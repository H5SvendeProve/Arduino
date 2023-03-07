#include <Wire.h>
String dataFromMaster;

void setup() {
  Serial.begin(9600);
  Wire.begin(0x08);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void sendData() {
  Serial.println("data resve");
  if(dataFromMaster == "110"){
    Wire.write("True ");
  }
  else{
    Wire.write("False");
  }
}

void receiveEvent(int bytes) {
  String message = "";
  while (Wire.available()) {
    char c = Wire.read();
    message += c;          
  }
  if(message != ""){
   Serial.println(message);
   dataFromMaster = message;
  }
}
