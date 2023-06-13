#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
#define DHTPIN 7
#define DHTTYPE DHT22
float temp, hum;
DHT dht(DHTPIN, DHTTYPE);

#define MPU_addr 0b01101000
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x01101011);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
  temp = dht.readTemperature();
  hum  = dht.readHumidity();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    // Shifting 
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Tmp = (Tmp/340.00) + 36.53;
  lcd.setCursor(0, 0);
  lcd.print("    GAUL NEBULA    ");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(temp);
  lcd.setCursor(0, 2);
  lcd.print("Humidty:     ");
  lcd.print(hum);
  lcd.setCursor(0, 3);
  lcd.print(AcX);
  lcd.print("|");
  lcd.print(AcY);
  lcd.print("|");
  lcd.print(AcZ);
  delay(1000);
}
