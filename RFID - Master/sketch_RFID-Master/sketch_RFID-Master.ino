#include <SPI.h>
#include <Wire.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
#define Led_PIN 8

RFID rfid(SS_PIN, RST_PIN);
String inputRfidCard;

String rfidCardLEDON = "203 17 205 34";
String rfidCardLEDOFF = "1 233 208 46";

String rfidCardHomeON = "57 144 80 153";
String rfidChipHomeOFF = "9 146 39 164";

int VaskemaskineId = 0x09;

void setup() {
  Serial.begin(9600);
  pinMode(Led_PIN, OUTPUT);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  Wire.begin();
  rfid.init();
}
void loop() {
  readRfidcard();
  turnLedOnWithDelay(rfidCardLEDON);
  if(inputRfidCard == rfidCardLEDON){
    Serial.println("Inside Loop => if(inputcard == homecard)");
    //Wire.beginTransmission(0x08);
    //Wire.write("110");
    //Wire.endTransmission();
    
    writeI2C(0x08, "110");
    
    delay(500);
    Wire.requestFrom(0x08, 32);
    String respons = "";
    while(Wire.available()) {
      char c = Wire.read();
      if (c >= 32 && c <= 126) { // only adds ASCII chars
        respons += c;
      }
    }
  Serial.println("response: " + String(respons));

  String machineType = GetWhitchMachine(respons);
  if(machineType == "Vaskemaskine"){
    String WriteToScreen = getDataForeScreen(respons);
    const char* WriteToScreenChar = WriteToScreen.c_str();
    Wire.beginTransmission(0x09);
    //Wire.write("Start vaskemaskine");
    Wire.write(WriteToScreenChar);
    Wire.endTransmission();
  }
  
  //if(respons == "True " ){
  //  Serial.println("inside if(res == True)");
  //  Wire.beginTransmission(0x09);
  //  Wire.write("Start vaskemaskine");
  //  Wire.endTransmission();
  //}
  
    //writeI2C(0x09, "Start vaskemaskine");
  }


  resetInputRfidCard();
}

void turnLedOnWithDelay(String rfidCard){
  if(inputRfidCard == rfidCard){
    Serial.println("turnLedOnWithDelay => if(rfidCard == rfidCard)");
    digitalWrite(Led_PIN, HIGH);
    delay(100);
    digitalWrite(Led_PIN, LOW);
  }
  //resetInputRfidCard();
}

void turnLedOnOff(String rfidCardOn, String rfidCardOff){
  if(inputRfidCard == rfidCardLEDON){
    digitalWrite(Led_PIN, HIGH);
    }
  else if(inputRfidCard == rfidCardLEDOFF){
    digitalWrite(Led_PIN, LOW);
  }
  //resetInputRfidCard();
}

void resetInputRfidCard(){
  inputRfidCard = "";
}

void readRfidcard(){
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      inputRfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(inputRfidCard);
    }
      rfid.halt();
  }
}

void writeI2C(int address, char* content){
  Serial.println("Wire transmission started");
  Wire.beginTransmission(address);
  Wire.write(content);
  Wire.endTransmission();
  Serial.println("Wire transmission ended");
}

String GetWhitchMachine(String input){
  int indexOfKoma1 = input.indexOf(',') + 2;
  int indexOfKoma2 = input.indexOf(',', indexOfKoma1) + 1;
  Serial.println("=====================");
  Serial.println(indexOfKoma1);
  Serial.println(indexOfKoma2);
  Serial.println("=====================");
  String substr = input.substring(indexOfKoma2);
  Serial.println("sub string: " + substr);
  return substr;
}

String getDataForeScreen(String input){
  int indexOfKoma1 = input.indexOf(',') + 2;
  int indexOfKoma2 = input.indexOf(',', indexOfKoma1) + 1;
  Serial.println("=====================");
  Serial.println(indexOfKoma1);
  Serial.println(indexOfKoma2);
  Serial.println("=====================");
  String output = input.substring(0, indexOfKoma2 - 1);
  Serial.println(output);

  return output;
}
