#include "i2c.h"

String dataFromMaster;
bool makeWebrequset = false;
char host[] = HOST;
char path[] = PATH;

void setupI2C(){
  Wire.begin(0x08);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveEvent);
}

void sendData() {
  Serial.println("data received");
  if(makeWebrequset){
    String respones = sendHttpRequsetchar(host, path);
 
    String statusCode = httpRequsetPareser_StatusCode(respones);
    Serial.println(statusCode);    
    if(statusCode != "200 OK"){
      Serial.println("if(statusCode != 200 OK){");
      String toMaster = httpRequsetPareser(respones);
      String responseToMaster = pareseModule(toMaster);
      const char* responseToMasterChar = responseToMaster.c_str();
      Wire.write(responseToMasterChar);
      //Wire.write("True ");
    } else{
      Wire.write("False");
    }
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
   makeWebrequset = true;
  }
}
