#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define vaskemaskinePin 8
//#define closeDoorPin 9

LiquidCrystal_I2C lcd(0x27,16,2);
String dataFromMaster;
int btnState = 0;
bool machineInUse = false;

void setup() {
  Wire.begin(0x09);
  lcd.backlight();
  Wire.onReceive(receiveEvent);
  pinMode(vaskemaskinePin, OUTPUT);
  //pinMode(closeDoorPin, INPUT);
  Serial.begin(9600);
  //pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR_btnPressed, HIGH);
  lcd.init();
  lcd.clear();
}

void loop() {
  delay(100);
  //if(dataFromMaster == "Start vaskemaskine")
  if(machineInUse)
  {
    //lcd.init();
    //lcd.clear();         
  
    //lcd.setCursor(3,0);
    //lcd.print("Load");
    //WriteToScreen(dataFromMaster);
    //btnState = digitalRead(closeDoorPin);
    Serial.println(btnState);
    if(btnState){
      //Serial.println("btn pressed");
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
  } else {
    WriteToScreen("Scan RFID kort");
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
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) 
  {
    Serial.println("btn pressed doooooooooown CHANGE");
    //btnState = 1;
    btnState = !btnState;
  }
  last_interrupt_time = interrupt_time;

}

void runWash(int timeInMin){
  digitalWrite(vaskemaskinePin, HIGH);
  int timeInSec = 60 / timeInMin;
  for(int i = 0; i < timeInSec; i++){
    //Serial.println("runing");
    delay(250);
    int timeLeft = timeInSec - i;
    screenTime(timeLeft);
  }
  delay(500);
  emtyMachineScreen();
  resetMachine();
}

void emtyMachineScreen(){
  WriteToScreen("Tom maskineren");
  digitalWrite(vaskemaskinePin, LOW);
  while(btnState == 1){
    Serial.println("indside: while(btnState == 1)");
  }
}

void screenTime(int remainingTime){
  lcd.setCursor(0,1);
  String timeFormated = "";
  if(remainingTime < 100 && remainingTime >= 10){
    //lcd.print("Time left: 0" + String(remainingTime));
    timeFormated = "0" + String(remainingTime);
  } else if (remainingTime < 10){
    timeFormated = "00" + String(remainingTime);
  } else {
    timeFormated = String(remainingTime);
    //lcd.print("Time left: " + String(remainingTime));
  }
  Serial.println("btn start: " + String(btnState));
  lcd.print("Time left: " + timeFormated);
}

void resetMachine(){
  dataFromMaster = "";
  digitalWrite(vaskemaskinePin, LOW);
  btnState = 0;
  lcd.clear();
  machineInUse = false;
}
