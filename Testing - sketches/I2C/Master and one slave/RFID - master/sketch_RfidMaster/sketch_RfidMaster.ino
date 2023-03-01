#include <SPI.h>
#include <Wire.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
#define Led_PIN 8

RFID rfid(SS_PIN, RST_PIN);
String rfidCard;

String rfidCardLEDON = "203 17 205 34";
String rfidCardLEDOFF = "1 233 208 46";
void setup() {
  Serial.begin(9600);
  pinMode(Led_PIN, OUTPUT);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  Wire.begin();
  rfid.init();
}
void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      if(rfidCard == rfidCardLEDON){
        digitalWrite(Led_PIN, HIGH);
        Serial.println("Wire transmission started");
        Wire.beginTransmission(0x08);   // start communication with slave at address 0x08
        Wire.write("start");                 // send a byte of data
        Wire.endTransmission();
        Serial.println("Wire transmission ended");
      }
      else if(rfidCard == rfidCardLEDOFF){
        digitalWrite(Led_PIN, LOW);
      }
    }
    rfid.halt();
  }

  //Serial.println("Prgram start");
}
