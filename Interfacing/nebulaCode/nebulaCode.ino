#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
/*
Gaul Avionic 
NEBULA 2023
Firmware
*/
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

Adafruit_BMP085 bmp;
float alt0;
void setup() {
  Serial.begin(115200);

    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G) || !bmp.begin())
  {
    Serial.println("Could not find one valid sensor, check wiring!");
    delay(500);
  }
  Serial.print(alt0);
  alt0 = bmp.readAltitude();
}

void getBmpData();
void getMpu6050Data();
void loop() {
    getBmpData();
    getMpu6050Data();
    delay(500);
}

void getBmpData(){
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude()) - alt0;
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");


    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
}

void getMpu6050Data(){
  Vector norm = mpu.readNormalizeGyro();
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);
}