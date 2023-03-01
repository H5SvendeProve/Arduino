#include <Wire.h>

void setup() {
  Wire.begin(0x08);       // initialize I2C interface as slave with address 0x08
  Wire.onReceive(receiveEvent);  // register receiveEvent function
  Serial.begin(9600);     // initialize serial communication
}

void loop() {
  delay(100);  // wait for incoming data
}

void receiveEvent(int bytes) {
  String message = "";
  while (Wire.available()) {
    char c = Wire.read();  // read the incoming byte
    message += c;          // append the character to the message string
  }
  Serial.println(message); // print the received string
}
