#include <Wire.h>
#include <WiFi101.h>
//#include <SPI.h>
#include "config.h"

char ssid[] = SSID;
char pass[] = PASSWORD;
char host[] = HOST;
char path[] = PATH;
int status = WL_IDLE_STATUS;

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
  String respones = sendHttpRequset(host, path);
  Serial.println("respones: " + String(respones));
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
    delay(10000);
  }
  Serial.println("Connected to wifi");
}

String sendHttpRequset(const char* host, const char* path){
  String message = "";
  WiFiClient client; //move later
    if(client.connect(host, 80)){
     Serial.println("Connected to server");
     
     client.print("GET " + String(path) + " HTTP/1.1\r\n");
     client.print("Host: " + String(host) + "\r\n");
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
    delay(5000);
     
  } else {
    Serial.println("Connection failed");
  }
  return message;
}
