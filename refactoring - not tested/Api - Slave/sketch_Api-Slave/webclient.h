#ifndef WEBCLIENT_H
#define WEBCLIENT_H
#include <Arduino.h>
#include <WiFi101.h>
#include "config.h"

void connecteToWifi();
String sendHttpRequsetchar(const char* host, const char* path);

#endif
