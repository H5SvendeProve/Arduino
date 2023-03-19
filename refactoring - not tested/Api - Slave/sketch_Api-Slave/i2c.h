#ifndef I2C_H
#define I2C_H
#include <Arduino.h>
#include <Wire.h>
#include "webclient.h"
#include "config.h"

void setupI2C();
void sendData();
void receiveEvent(int bytes);

#endif
