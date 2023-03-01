#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define DATA_SIZE 6

byte data[DATA_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
int data_index = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);      // initialize I2C bus with slave address
  Wire.onRequest(requestEvent);   // set onRequest event handler
}

void loop() {
  // do other stuff if needed
}

void requestEvent() {
  Wire.write(data[data_index]);   // send data byte
  data_index = (data_index + 1) % DATA_SIZE;  // increment data index and wrap around if needed
}
