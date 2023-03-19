#include "parser.h"

String GetWhitchMachine(String input){
  int indexOfKoma1 = input.indexOf(',') + 2;
  int indexOfKoma2 = input.indexOf(',', indexOfKoma1) + 1;
  String substr = input.substring(indexOfKoma2);
  Serial.println("sub string: " + substr);
  return substr;
}

String getDataForeScreen(String input){
  int indexOfKoma1 = input.indexOf(',') + 2;
  int indexOfKoma2 = input.indexOf(',', indexOfKoma1) + 1;
  String output = input.substring(0, indexOfKoma2 - 1);
  Serial.println(output);

  return output;
}
