#include <Adafruit_BMP085.h> //Need to download Adafruit lib
float temperature, altitude, alt0;
int32_t pressure;

Adafruit_BMP085 bmp;

/*
Wiring:
BMP    |     Arduino
------------------
Vcc -------> 3.3V
Gnd -------> Ground
SDA -------> A4
SCL -------> A5
*/
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()){ 
    // Check if the sensor is well wired
     Serial.println("The BMP is not detected, check Wiring!");
     while (1){

     }
  }
  alt0 = bmp.readAltitude();
  Serial.print("Initial Altitude");
  Serial.println(alt0);

}

void loop() {
  temperature = bmp.readTemperature();
  altitude = bmp.readAltitude() - alt0 ; // Set our initial position to 0
  pressure = bmp.readPressure() / 1000; //Load the pressure in KPa
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Altitude: ");
  Serial.println(altitude);
  Serial.print("Pressure: ");
  Serial.println(pressure);

  //Serial.println()
  delay(1000);
}
