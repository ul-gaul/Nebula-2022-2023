#define SYNC 0xFF
#define DATA_SIZE 7

#define SYNC_BIT 0
#define SIZE 1

#define X 2
#define Y 3
#define Z 4

#define SUM1 5
#define SUM2 6

#include <Arduino.h>
#include "CRC.h"

CRC16 crc(0x8005, 0xFFFF, 0x0, true, true); //init crc Algo = MODBUS

void    CrcCalc(uint8_t data[]);
bool    SendPacket(uint8_t data[]);

void setup() 
{
   Serial.begin(57600);
}

void loop()
{
   uint8_t data[DATA_SIZE];

   data[SYNC_BIT] = SYNC;
   data[SIZE] = sizeof(data);
   data[X] = 0x01;
   data[Y] = 0x55;
   data[Z] = 0x88;

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