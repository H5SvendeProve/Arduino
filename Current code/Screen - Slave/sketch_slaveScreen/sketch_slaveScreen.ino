#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define vaskemaskinePin 8

LiquidCrystal_I2C lcd(0x27,16,2);
String dataFromMaster;
int btnState = 0;
bool machineInUse = false;
String ProgramToRun = "null program";
int timeToRun = 0;

void setup() {
  Wire.begin(0x09);
  lcd.backlight();
  Wire.onReceive(receiveEvent);
  pinMode(vaskemaskinePin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), ISR_btnPressed, HIGH);
  lcd.init();
  lcd.clear();
}

void loop() {
  delay(100);
  if(machineInUse)
  {
    if(btnState){
      parseData(dataFromMaster);
      WriteToScreen(ProgramToRun, 0);
      runWash(timeToRun);
    } else  {
      WriteToScreen("Load", 3);
    }
  } else {
    WriteToScreen("Scan RFID kort", 0);
    delay(30);
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
  machineInUse = true;
}

void WriteToScreen(String text, int pos){
  delay(25);
  lcd.clear();         
  lcd.setCursor(0,0);
  lcd.print(text);
  delay(25);
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
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 500) 
  {
    Serial.println("btn pressed ISR");
    btnState = !btnState;
  }
  last_interrupt_time = interrupt_time;
}

void runWash(int timeInMin){
  digitalWrite(vaskemaskinePin, HIGH);
  for(int i = 0; i < timeInMin; i++){
    delay(150);
    int timeLeft = timeInMin - i;
    screenTime(timeLeft);
  }
  delay(500);
  emtyMachineScreen();
  resetMachine();
}

void emtyMachineScreen(){
  WriteToScreen("Tom maskineren", 0);
  digitalWrite(vaskemaskinePin, LOW);
  while(btnState == 1){
    Serial.println("indside: while(btnState == 1)");
  }
}

void screenTime(int remainingTime){
  lcd.setCursor(0,1);
  String timeFormated = "";
  if(remainingTime < 100 && remainingTime >= 10){
    timeFormated = "0" + String(remainingTime);
  } else if (remainingTime < 10){
    timeFormated = "00" + String(remainingTime);
  } else {
    timeFormated = String(remainingTime);
  }
  lcd.print("Time left: " + timeFormated);
}

void resetMachine(){
  dataFromMaster = "";
  digitalWrite(vaskemaskinePin, LOW);
  btnState = 0;
  lcd.clear();
  machineInUse = false;

  String ProgramToRun = "null program";
  int timeToRun = 0;
}

void parseData(String input){
  int indexOfKoma1 = input.indexOf(',') + 1;
  int indexOfKoma2 = input.indexOf(',', indexOfKoma1) + 1;
  ProgramToRun = input.substring(0, indexOfKoma1 - 1);
  timeToRun = (input.substring(indexOfKoma1, indexOfKoma2 - 1)).toInt();
  
  Serial.println("Program to run: " + ProgramToRun);
  Serial.println("Time to run: " + String(timeToRun));
}
