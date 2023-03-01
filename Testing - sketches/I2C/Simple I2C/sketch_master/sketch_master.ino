#include <Wire.h>

void setup() {
  Wire.begin();        // initialize I2C interface
  Serial.begin(9600);  // initialize serial communication
}

void loop() {
  Wire.beginTransmission(0x08);   // start communication with slave at address 0x08
  Wire.write("jdje");                 // send a byte of data
  Wire.endTransmission();         // end communication

  delay(1000);                     // wait for 1 second before repeating
}
