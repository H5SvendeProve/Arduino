#include "rfid.h"

String inputRfidCard;

RFID rfid(SS_PIN, RST_PIN);

void setupRFID(){
  pinMode(Led_PIN, OUTPUT);
  rfid.init();
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
