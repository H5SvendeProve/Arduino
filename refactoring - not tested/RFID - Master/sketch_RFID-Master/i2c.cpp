#include "i2c.h"


void setupI2C(){
  Wire.begin();
}

void writeI2C(int address, char* content){
  Serial.println("Wire transmission started");
  Wire.beginTransmission(address);
  Wire.write(content);
  Wire.endTransmission();
  Serial.println("Wire transmission ended");
}

String requestI2C(int address){
    Wire.requestFrom(address, 32);
    String respons = "";
    while(Wire.available()) {
      char c = Wire.read();
      if (c >= 32 && c <= 126) { // only adds ASCII chars
        respons += c;
      }
    }
    Serial.println("response: " + String(respons));
    return respons;
}
