#include <Arduino.h>
#include "CRC.h"
#include <TinyGPS++.h>

#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;

union U_float
{
  float v;
  uint8_t b[4];
};

// definition des capteurs:
Adafruit_BMP085 bmp;

//MPU6050 mpu;
//float timeStep = 0.01; //step pour calcul du gyroscope
//U_float pitch = 0;
//U_float roll = 0;
//U_float yaw = 0;


//definition des pins:
const int InputFix = 23;  //pin pour déterminer s'il y a un fix sur le gps
const int LedFix = A4;

unsigned long previousMillis = 0;
const long intervalBlink = 1000;

unsigned long previousMillisComm = 0;
const long intervalComm = 10;

const int SYNC = 0xFF;
const int DATA_SIZE = 28; //Packet structure size;
const int SIZE_FLOAT = sizeof(float); //4

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

const int ROLL0      = 10;
const int ROLL1      = 11;
const int ROLL2      = 12;
const int ROLL3      = 13;

const int YAW0       = 14;
const int YAW1       = 15;
const int YAW2       = 16;
const int YAW3       = 17;

const int LAT0       = 18;
const int LAT1       = 19;
const int LAT2       = 20;
const int LAT3       = 21;

const int LON0       = 22;
const int LON1       = 23;
const int LON2       = 24;
const int LON3       = 25;

const int SUM0       = 26;
const int SUM1       = 27;

CRC16 crc(0x8005, 0xFFFF, 0x0, true, true); //init crc Algo = MODBUS

//Prototype
void     CrcCalc(uint8_t data[]);
bool     SendPacket(uint8_t data[]);
void     FloatToArray(U_float input, uint8_t output[]);
void     UpdateArray(uint8_t conv[], uint8_t address[]);

void setup() 
{
   pinMode(LedFix, OUTPUT);
   pinMode(InputFix, INPUT);

   Serial2.begin(9600);	//RX2 PIN 17 TX2 PIN 16 ----- GPS
   Serial.begin(57600); //RX0 PIN 0 TX0 PIN 1 ----- RXD900
}

void loop()
{
   uint8_t data[DATA_SIZE];
   uint8_t conv[SIZE_FLOAT];
   U_float alt, lat, lon, pitch, roll, yaw;


   if (Serial2.available() > 0)
   {
      gps.encode(Serial2.read());
   }
    
//GPS
   if(digitalRead(InputFix) == true)
   {
      digitalWrite(LedFix, HIGH);
   }
   else
   {
      digitalWrite(LedFix, LOW);
   }
  
   lat.v = gps.location.lat();
   lon.v = gps.location.lng();

//Altimetre

   alt.v = bmp.readAltitude();

//gyroscope 

   //norm = mpu.readNormalizeGyro();
   //normAccel = mpu.readNormalizeAccel();

// Calculate Pitch, Roll and Yaw

   //pitch.v = pitch.v + norm.YAxis * timeStep;
   //roll.v = roll.v + norm.XAxis * timeStep;
   //yaw.v = yaw.v + norm.ZAxis * timeStep;

   data[SYNC_BIT] = SYNC;
   data[SIZE] = sizeof(data);

   FloatToArray(alt, &conv[0]);       //Put the float value in the conv array
   UpdateArray(conv, &data[ALT0]);     //Put the value of conv in the packet at the address designed

   FloatToArray(roll, &conv[0]);
   UpdateArray(conv, &data[ROLL0]);

   FloatToArray(pitch, &conv[0]); 
   UpdateArray(conv, &data[PITCH0]);    

   FloatToArray(yaw, &conv[0]);       
   UpdateArray(conv, &data[YAW0]);    


   FloatToArray(lat, &conv[0]);       
   UpdateArray(conv, &data[LAT0]);

   FloatToArray(lon, &conv[0]);       
   UpdateArray(conv, &data[LON0]);


  //Code pour creer des delais sans la fonction delay... -------------------------- A VOIR SI LES DELAYS FONCTIONNE BIEN. LA LED SUR LA PIN A4 FLASH TU ?
  //delay LED d'indication 
   unsigned long currentMillis = millis();
   if (currentMillis - previousMillis >= intervalBlink)
   {
      previousMillis = currentMillis;
      if (LedFix == LOW){LedFix = HIGH;}
      else {LedFix = LOW;}
   }
   

   //delay communicaton ------------------------------------------------------------SI LES DELAYS FONCTIONNE PAS ON SEND PAS LE PACKET ICI
   unsigned long currentMillisComm = millis();
   if (currentMillisComm - previousMillisComm >= intervalComm)
   {
      previousMillisComm = currentMillisComm;
      CrcCalc(data);
      SendPacket(data);
   }
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
