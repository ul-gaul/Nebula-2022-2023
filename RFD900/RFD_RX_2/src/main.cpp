#define BUFFER_SIZE 30
#define CLEAR_SERIAL Serial.println("\033[0H\033[0J");

#include <Arduino.h>
#include "CRC.h"

union U_float
{
  float v;
  uint8_t b[4];
};

const int SYNC = 0xFF;
const int DATA_SIZE = 20; //Packet structure size;
const int SIZE_FLOAT = sizeof(float); //4
const uint16_t period = 500; // 1/2 seconde

//Packet structure
const int SYNC_BIT   = 0;
const int SIZE       = 1;

const int ALT0       = 2;
const int ALT1       = 3;
const int ALT2       = 4;
const int ALT3       = 5;

const int PITCH0     = 6;
const int PITCH1     = 7;
const int PITCH2     = 8;
const int PITCH3     = 9;

const int ROLL0     	= 10;
const int ROLL1     	= 11;
const int ROLL2     	= 12;
const int ROLL3    	= 13;

const int YAW0     	= 14;
const int YAW1     	= 15;
const int YAW2     	= 16;
const int YAW3     	= 17;

const int SUM1       = 18;
const int SUM2       = 19;

CRC16 crc(0x8005, 0xFFFF, 0x0, true, true); //init crc Algo = MODBUS

uint16_t startMillis;
uint16_t currentMillis;

//Prototype
uint16_t		CrcCalc(uint8_t data[], bool update = false);
bool			CrcCheck(uint8_t data[]);
bool			SendPacket(uint8_t data[]);
void			ShowData(uint8_t data[]);

void setup()
{
  Serial.begin(57600);
  Serial2.begin(57600);
}

void loop()
{
  	uint8_t data[DATA_SIZE];

	memset(data, 0, sizeof(data));

	data[SYNC_BIT] = SYNC;
	data[SIZE] = sizeof(data);

	if(Serial2.available()>data[SIZE])
	{
		startMillis = millis();
		
		while(Serial2.read() != SYNC)
		{
			currentMillis = millis();
			if(currentMillis - startMillis >= period){break;}
		}
		Serial2.read();
		for (uint8_t i = 2; i < data[SIZE]; i++)
		{
			data[i] = Serial2.read();
		}
	}

  	if(CrcCheck(data))
  	{
   	CLEAR_SERIAL
    	Serial.println("Pass!");
    	ShowData(data);    
  	}
	else if(((uint16_t)data[SUM1] << 8) | data[SUM2] != 0)
	{
    	CLEAR_SERIAL
    	Serial.println("Error!");
    	ShowData(data);
  	}
  
  	delay(10);
}

//Crc16 calculation.
uint16_t	CrcCalc(uint8_t data[], bool update)
{   
   uint16_t sum;

   crc.restart();

   for (uint8_t i = 0; i < data[SIZE]-2; i++)
   {
      crc.add(data[i]);
   }

   sum = crc.calc();

	if(update)
	{
		data[data[SIZE]-1]=sum & 0xff;
   	data[data[SIZE]-2]=(sum >> 8);
	}
   
	return sum;
}

//If the packet is clean we got True
bool CrcCheck(uint8_t data[])
{
	uint16_t temp = CrcCalc(data);
	uint16_t checksum = ((uint16_t)data[SUM1] << 8) | data[SUM2];

  	if(temp == checksum)
  	{
   	return true;
  	}
  	return false;
}

void ShowData(uint8_t data[])
{
	for (uint8_t i = 0; i < data[SIZE]; i++)
	{
		Serial.print(data[i], HEX);
	}
	
}