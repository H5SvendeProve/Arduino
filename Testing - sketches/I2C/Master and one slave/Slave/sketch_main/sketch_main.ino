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
  if(message != ""){
   Serial.println(message); // print the received string 
  }
  
  //Wire.beginTransmission(0x09);   // start communication with slave at address 0x08
  //Wire.write("hej");            // send a byte of data
  //Wire.endTransmission();         // end communication
}
