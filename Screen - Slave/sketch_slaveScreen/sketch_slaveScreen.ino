#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
String dataFromMaster;

void setup() {
  Wire.begin(0x09);
  lcd.backlight();
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
  if(dataFromMaster == "Start vaskemaskine")
  {
    WriteToScreen();
    //serialScreenErrorLog();
  }
}

void receiveEvent(int bytes) {
  String message = "";
  while (Wire.available()) {
    char c = Wire.read();
    message += c;
  }
  Serial.println(message);
  dataFromMaster = message;
}

void WriteToScreen(){
  lcd.init();
  lcd.clear();         
  
  lcd.setCursor(3,0);
  lcd.print("Load");
  
  delay(3000);
  lcd.clear();         
  
  lcd.setCursor(1,0);
  lcd.print("Koge vask");
  
}

void serialScreenErrorLog(){
    int nDevices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {

    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}
