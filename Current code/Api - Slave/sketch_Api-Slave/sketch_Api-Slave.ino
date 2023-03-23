#include <Wire.h>
#include <WiFi101.h>
//#include <SPI.h>
#include "config.h"
#include "parser.h"

char ssid[] = SSID;
char pass[] = PASSWORD;
char host[] = HOST;
char path[] = PATH;
int status = WL_IDLE_STATUS;

String apiKey = APIKEY;
String masterArduinoId = MASTERARDUINOID;

String dataFromMaster;
bool makeWebrequset = false;

void setup() {
  startSerial();
  connecteToWifi();
  Wire.begin(0x08);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void sendData() {
  Serial.println("data received");
  if(makeWebrequset){
    String fullPath = String(path) + String(dataFromMaster);
    Serial.println("path:       " + String(path));
    Serial.println("build path: " + fullPath );
    const char* fullPathChar = fullPath.c_str();
    Serial.println("char path:  " + String(fullPathChar));
    String respones = sendHttpRequsetchar(host, fullPathChar);
    
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
      Serial.println("if(statusCode != 200 OK){} else{");
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
   Serial.println("==============================================");
   Serial.println("dataFromMaster: " + String(dataFromMaster));
   Serial.println("==============================================");
   makeWebrequset = true;
  }
  else{
    makeWebrequset = false;
  }
}

void startSerial(){
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}

void connecteToWifi(){
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(2000);
  }
  Serial.println("Connected to wifi");
}



String sendHttpRequsetchar(const char* host, const char* path){
  String message = "";
  WiFiClient client;
    if(client.connect(host, 80)){
     Serial.println("Connected to server");
     
     client.print("GET " + String(path) + " HTTP/1.1\r\n");
     client.print("Host: " + String(host) + "\r\n");
     client.print("X-Api-Key: " + String(apiKey) + "\r\n");
     client.print("X-MasterArduinoId: " + String(masterArduinoId) + "\r\n");
     client.print("Connection: close\r\n\r\n");

     while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        message = message + c;
      }
    }

    client.stop();
    Serial.println("Disconnected from server");   
  } else {
    Serial.println("Connection failed");
  }
  Serial.println("returns");
  return message;
}
