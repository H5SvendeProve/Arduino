#include <Wire.h>

void setup() {
  Wire.begin(); 
  Serial.begin(9600); 
}

void loop() {
  Wire.beginTransmission(0x08);
  int error = Wire.endTransmission();
  if (error == 0) {
    Serial.println("Slave device is connected!");
  Wire.requestFrom(0x08,1);     // request 6 bytes of data from device with I2C address 0x68

  while (Wire.available()) {     // loop through all received bytes
    byte data = Wire.read();     // read data byte
    Serial.print(data);     // print data in hexadecimal format
    Serial.print(" ");           // print space between bytes
  }
  Serial.println(); 
  } else {
    Serial.println("Slave device is not connected!");
  }
  delay(1000);
}
