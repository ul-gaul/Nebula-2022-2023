#include <Arduino.h>
#include "CRC.h"

union U_float
{
  float v;
  uint8_t b[4];
};

const int SYNC = 0xFF;
const int DATA_SIZE = 11; //Packet structure size;
const int SIZE_FLOAT = sizeof(float); //4

//Packet structure
const int SYNC_BIT   = 0;
const int SIZE       = 1;
const int X          = 2;
const int Y          = 3;
const int Z          = 4;
const int ALT0       = 5;
const int ALT1       = 6;
const int ALT2       = 7;
const int ALT3       = 8;
const int SUM1       = 9;
const int SUM2       = 10;

CRC16 crc(0x8005, 0xFFFF, 0x0, true, true); //init crc Algo = MODBUS

//Prototype
void     CrcCalc(uint8_t data[]);
bool     SendPacket(uint8_t data[]);
void     FloatToArray(U_float input, uint8_t output[]);
void     UpdateArray(uint8_t conv[], uint8_t address[]);

void setup() 
{
   Serial.begin(57600);
}

void loop()
{
   uint8_t data[DATA_SIZE];

   U_float test;

   test.v = 1247.4785;

   uint8_t conv[SIZE_FLOAT];

   data[SYNC_BIT] = SYNC;
   data[SIZE] = sizeof(data);
   data[X] = 0x01;
   data[Y] = 0x55;
   data[Z] = 0x88;

   FloatToArray(test, &conv[0]);       //Put the float value in the conv array
   UpdateArray(conv, &data[ALT0]);     //Put the value of conv in the packet at the address designed

   CrcCalc(data);

   SendPacket(data);
   
  delay(10);
}

//Crc16 calculation.
void CrcCalc(uint8_t data[])
{   
   uint16_t sum;

   crc.restart();

   for (uint8_t i = 0; i < data[SIZE]-2; i++)
   {
      crc.add(data[i]);
   }

   sum = crc.calc();

   data[data[SIZE]-1]=sum & 0xff;
   data[data[SIZE]-2]=(sum >> 8);
}

bool SendPacket(uint8_t data[])
{
   Serial.write(data, data[SIZE]);
   return true;
}

void FloatToArray(U_float input, uint8_t output[])
{
   for (int i = 0; i < SIZE_FLOAT; i++) 
   {
      output[i] = input.b[i];
   }
}

void UpdateArray(uint8_t conv[], uint8_t address[])
{
   for (int i = 0; i < SIZE_FLOAT; i++) 
   {
      address[i] = conv[i];
   }
}