#include <Wire.h>

void setup() {
  Wire.begin(); // initialize I2C communication
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  Wire.beginTransmission(8);
  Wire.write("110");
  Wire.endTransmission();
  
  delay(500); // wait before requesting data from slave
  Wire.requestFrom(8, 5); // request 5 bytes from slave device with address 8
  String respons = "";
  while(Wire.available()) { // wait for data to be available
    char c = Wire.read(); // read the received byte
    respons += c;
  }
  Serial.println(respons);
  if(respons == "True " ){
    Serial.println("inside if(res == True)");
    Wire.beginTransmission(0x09);
    Wire.write("Start vaskemaskine");
    Wire.endTransmission();
  }
  
  delay(500); // wait before sending data again
}
