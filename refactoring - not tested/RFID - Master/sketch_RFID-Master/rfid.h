#ifndef RFID_H
#define RFID_H
#include <Arduino.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
#define Led_PIN 8

extern String inputRfidCard;

void setupRFID();
void resetInputRfidCard();
void readRfidcard();


#endif
