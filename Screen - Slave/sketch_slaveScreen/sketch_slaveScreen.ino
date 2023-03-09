#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define vaskemaskinePin 8
//#define closeDoorPin 9

LiquidCrystal_I2C lcd(0x27,16,2);
String dataFromMaster;
int btnState = 0;

void setup() {
  Wire.begin(0x09);
  lcd.backlight();
  Wire.onReceive(receiveEvent);
  pinMode(vaskemaskinePin, OUTPUT);
  //pinMode(closeDoorPin, INPUT);
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR_btnPressed, CHANGE);
  lcd.clear();
}

void loop() {
  delay(100);
  if(dataFromMaster == "Start vaskemaskine")
  {
  lcd.init();
  lcd.clear();         
  
  lcd.setCursor(3,0);
  lcd.print("Load");
    //WriteToScreen(dataFromMaster);
    //btnState = digitalRead(closeDoorPin);
    Serial.println(btnState);
    if(btnState){
      Serial.println("btn pressed");
      WriteToScreen(dataFromMaster);
      //digitalWrite(vaskemaskinePin, HIGH);
      runWash(1);
    } else  {
      lcd.clear();   
            
      lcd.setCursor(3,0);
      lcd.print("Load");
    }
    //digitalWrite(vaskemaskinePin, HIGH);
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

void WriteToScreen(String program){
  //lcd.init();
  //lcd.clear();         
  
  //lcd.setCursor(3,0);
  //lcd.print("Load");
  
  //delay(3000);
  lcd.clear();         
  
  lcd.setCursor(1,0);
  lcd.print(program);
  
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

void ISR_btnPressed(){
  
  //Serial.println("btn pressed doooooooooown CHANGE");
  btnState = 1;

}

void runWash(int timeInMin){
  digitalWrite(vaskemaskinePin, HIGH);
  int timeInSec = 60 / timeInMin;
  for(int i = 0; i < timeInSec; i++){
    //Serial.println("runing");
    delay(500);
    int timeLeft = timeInSec - i;
    screenTime(timeLeft);
  }
  resetMachine();
}

void screenTime(int remainingTime){
  lcd.setCursor(0,1);
  if(remainingTime < 10){
    lcd.print("Time left: 0" + String(remainingTime));
  } else {
    lcd.print("Time left: " + String(remainingTime));
  }
  
}

void resetMachine(){
  dataFromMaster = "";
  digitalWrite(vaskemaskinePin, LOW);
  btnState = 0;
  lcd.clear();
}
