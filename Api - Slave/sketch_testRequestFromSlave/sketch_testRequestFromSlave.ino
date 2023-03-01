#include <Wire.h>
String dataFromMaster;

void setup() {
  Serial.begin(9600);
  Wire.begin(8); // initialize I2C communication with slave address 8
  Wire.onRequest(sendData); // register the sendData function to handle master's request
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void sendData() {
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
