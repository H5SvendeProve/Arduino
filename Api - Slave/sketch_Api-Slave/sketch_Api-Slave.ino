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
  //Serial.begin(9600);
  startSerial();
  connecteToWifi();
  Wire.begin(0x08);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
  //Serial.print("*");
}

void sendData() {
  Serial.println("data received");
  //String respones = sendHttpRequset(host, path);
  //Serial.println("respones: " + String(respones));
  if(makeWebrequset){
    ///const char* dataFormMasterChar = dataFromMaster.c_str();
    ///const char* fullPath[path + dataFormMasterChar +1];
    ///strcpy(fullPath, path);
    ///strcat(fullPath, dataFormMasterChar); 
    ///String respones = sendHttpRequsetchar(host, fullPath);

    String fullPath = String(path) + String(dataFromMaster);
    Serial.println("path:       " + String(path));
    Serial.println("build path: " + fullPath );
    const char* fullPathChar = fullPath.c_str();
    Serial.println("char path:  " + String(fullPathChar));
    String respones = sendHttpRequsetchar(host, fullPathChar);
    
    //Serial.println("hallo?");
    //Serial.println("respones: ");
    //Serial.println(respones);
    //Wire.write(respones);
    //String toMaster = httpRequsetPareser(respones);
    //Serial.println(toMaster);
    //char* myCharArray = (char*) toMaster;
    
    
    //Serial.println(toMaster);
    String statusCode = httpRequsetPareser_StatusCode(respones);
    //Serial.println("+++++++++++++++++++++");
    Serial.println(statusCode);    
    //Serial.println("+++++++++++++++++++++");
    //const char* myCharArray = toMaster.c_str();
    //Serial.println(myCharArray);
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
  
  //Serial.println("data resve");
  //if(dataFromMaster == "110"){
  //  Wire.write("True ");
  //}
  //else{
  //  Wire.write("False");
  //}
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
    //delay(10000);
    delay(2000);
  }
  Serial.println("Connected to wifi");
}



String sendHttpRequsetchar(const char* host, const char* path){
  String message = "";
  WiFiClient client; //move later
    if(client.connect(host, 80)){ // 80
     Serial.println("Connected to server");
     
     //client.print("GET " + String(path) + " HTTP/1.1\r\n");
     //client.print("Host: " + String(host) + "\r\n");
     //client.print("X-Api-Key: " + String("bIdn4xXkBOZteyJpRxXxIscgGJK1pM6W1OPF") + "\r\n");
     //client.print("X-MasterArduinoId: " + String("94ead0de-d462-4fd5-841c-a202bdb93eda") + "\r\n");
     //client.print("Connection: close\r\n\r\n");

     client.print("GET " + String(path) + " HTTP/1.1\r\n");
     client.print("Host: " + String(host) + "\r\n");
     client.print("X-Api-Key: " + String(apiKey) + "\r\n");
     client.print("X-MasterArduinoId: " + String(masterArduinoId) + "\r\n");
     //client.print("X-Api-Key: " + String("bIdn4xXkBOZteyJpRxXxIscgGJK1pM6W1OPF") + "\r\n");
     //client.print("X-MasterArduinoId: " + String("94ead0de-d462-4fd5-841c-a202bdb93eda") + "\r\n");
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
    //delay(5000);
     
  } else {
    Serial.println("Connection failed");
  }
  Serial.println("returns");
  return message;
}

//String httpRequsetPareser_StatusCode(String textToParse){
//  int indexOfSpace = textToParse.indexOf(' ') + 1;
//  int indexOfNewLine = textToParse.indexOf('\n');
//  String substr = textToParse.substring(indexOfSpace, indexOfNewLine);

//  //Serial.println(substr);
//  return substr;
//}

//String httpRequsetPareser(String textToParse){
//  //Serial.println("parser start:");
//  //Serial.println(textToParse);  // Prints the string with \n as a newline character
//  //Serial.println();     // Creates a new line
//  //Serial.println(textToParse);  // Prints the string with \n as a literal string
//  //Serial.println(textToParse);
//  //Serial.println("parser start 2:");
//  //String test = textToParse;
//  //test.replace("\\", "\\\\');
//  //Serial.println(test);
//  int indexStart = textToParse.indexOf("\r\n\r\n") + 8;
//  int indexEnd = textToParse.indexOf('\n', indexStart);
//  String substr = textToParse.substring(indexStart, indexEnd);
//  
//  Serial.println("parser: httprequsetparser");
//  //Serial.println(substr);
//  return substr;
//}
//
//String pareseModule(String textToParse){
//  int indexOfKoma1 = textToParse.indexOf(',') + 2;
//  int indexOfKoma2 = textToParse.indexOf(',', indexOfKoma1) + 2;
//  int indexOfKoma3 = textToParse.indexOf(',', indexOfKoma2) + 2;
//  //Serial.println("=====================");
//  //Serial.println(indexOfKoma1);
//  //Serial.println(indexOfKoma2);
//  //Serial.println(indexOfKoma3);
//  //Serial.println("=====================");
//  String substr1 = textToParse.substring(0, indexOfKoma1);
//  String substr2 = textToParse.substring(indexOfKoma1, indexOfKoma2);
//  String substr3 = textToParse.substring(indexOfKoma2, indexOfKoma3);
//  String substr4 = textToParse.substring(indexOfKoma3);
//  //Serial.println("####################");
//  //Serial.println(substr1);
//  //Serial.println(substr2);
//  //Serial.println(substr3);
//  //Serial.println(substr4);
//  //Serial.println("####################");
//  int indexStartSub1 = substr1.indexOf(':') + 2;
//  int indexEndSub1 = substr1.indexOf('"', indexStartSub1);
//  String programName = substr1.substring(indexStartSub1, indexEndSub1);
//  
//  int indexStartSub2 = substr2.indexOf(':') + 1;
//  int indexEndSub2 = substr2.indexOf(',', indexStartSub2);
//  String runTime = substr2.substring(indexStartSub2, indexEndSub2);
//
//  int indexStartSub3 = substr3.indexOf(':') + 2;
//  int indexEndSub3 = substr3.indexOf('"', indexStartSub3);
//  String manufacturer = substr3.substring(indexStartSub3, indexEndSub3);
//
//  int indexStartSub4 = substr4.indexOf(':') + 2;
//  int indexEndSub4 = substr4.indexOf('"', indexStartSub4);
//  String machineType = substr4.substring(indexStartSub4, indexEndSub4);
//  
//  //Serial.println("xxxxxxxxxxxxxxxxxxxx");
//  //Serial.println(programName);
//  //Serial.println(runTime);
//  //Serial.println(manufacturer);
//  //Serial.println(machineType);
//  //Serial.println("xxxxxxxxxxxxxxxxxxxx");
//
//  String output = String(programName) + "," + String(runTime) + "," + String(machineType);
//  Serial.println(output);
//  return output;
//}
