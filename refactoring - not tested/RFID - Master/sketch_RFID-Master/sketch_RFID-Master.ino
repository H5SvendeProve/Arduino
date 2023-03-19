#include "i2c.h"
#include "rfid.h"
#include "config.h"
#include "parser.h"

String rfidCardLEDON = RFIDCARDID1;
String rfidCardLEDOFF = RFIDCARDID2;

int VaskemaskineId = SCREENSLAVEI2CADDRESS;
int ApiSlaveAddress = APISLAVEI2CADDRESS;

void setup() {
  Serial.begin(9600);
  setupRFID();
  Serial.println("Starting the RFID Reader...");
  setupI2C();
}
void loop() {
  readRfidcard();
  turnLedOnWithDelay(rfidCardLEDON);
  if(inputRfidCard == rfidCardLEDON){
    Serial.println("Inside Loop => if(inputcard == homecard)");
    
    writeI2C(ApiSlaveAddress, "110");
    
    delay(500);
    String response = requestI2C(ApiSlaveAddress);
    
    String machineType = GetWhitchMachine(response);
    if(machineType == "Vaskemaskine"){
      String WriteToScreen = getDataForeScreen(response);
      const char* WriteToScreenChar = WriteToScreen.c_str();
      Wire.beginTransmission(0x09);
      Wire.write(WriteToScreenChar);
      Wire.endTransmission();
    }
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
}
