#ifndef I2C_H
#define I2C_H
#include <Arduino.h>
#include <Wire.h>

void setupI2C();
void writeI2C(int address, char* content);
String requestI2C(int address);

#endif
