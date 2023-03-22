#include "parser.h"

String httpRequsetPareser_StatusCode(String textToParse){
  int indexOfSpace = textToParse.indexOf(' ') + 1;
  int indexOfNewLine = textToParse.indexOf('\n');
  String substr = textToParse.substring(indexOfSpace, indexOfNewLine);

  Serial.println(substr);
  return substr;
}

String httpRequsetPareser(String textToParse){
  //Serial.println("parser start:");
  //Serial.println(textToParse);  // Prints the string with \n as a newline character
  //Serial.println();     // Creates a new line
  //Serial.println(textToParse);  // Prints the string with \n as a literal string
  //Serial.println(textToParse);
  //Serial.println("parser start 2:");
  //String test = textToParse;
  //test.replace("\\", "\\\\');
  //Serial.println(test);
  int indexStart = textToParse.indexOf("\r\n\r\n") + 8;
  int indexEnd = textToParse.indexOf('\n', indexStart);
  String substr = textToParse.substring(indexStart, indexEnd);
  
  Serial.println("parser: httprequsetparser");
  Serial.println("=== after parser http.. =============");
  Serial.println(substr);
  Serial.println("=====================================");
  return substr;
}

String pareseModule(String textToParse){
  int indexOfKoma1 = textToParse.indexOf(',') + 2;
  int indexOfKoma2 = textToParse.indexOf(',', indexOfKoma1) + 2;
  int indexOfKoma3 = textToParse.indexOf(',', indexOfKoma2) + 2;
  int indexOfKoma4 = textToParse.indexOf(',', indexOfKoma3) + 2;
  Serial.println("=====================");
  Serial.println(indexOfKoma1);
  Serial.println(indexOfKoma2);
  Serial.println(indexOfKoma3);
  Serial.println(indexOfKoma4);
  Serial.println("=====================");
  String substr1 = textToParse.substring(0, indexOfKoma1);
  String substr2 = textToParse.substring(indexOfKoma1, indexOfKoma2);
  String substr3 = textToParse.substring(indexOfKoma2, indexOfKoma3);
  String substr4 = textToParse.substring(indexOfKoma3, indexOfKoma4);
  String substr5 = textToParse.substring(indexOfKoma4);
  Serial.println("####################");
  Serial.println(substr1);
  Serial.println(substr2);
  Serial.println(substr3);
  Serial.println(substr4);
  Serial.println(substr5);
  Serial.println("####################");
  int indexStartSub1 = substr1.indexOf(':') + 2;
  int indexEndSub1 = substr1.indexOf('"', indexStartSub1);
  String programName = substr1.substring(indexStartSub1, indexEndSub1);
  
  int indexStartSub2 = substr2.indexOf(':') + 1;
  int indexEndSub2 = substr2.indexOf(',', indexStartSub2);
  String runTime = substr2.substring(indexStartSub2, indexEndSub2);

  int indexStartSub3 = substr3.indexOf(':') + 2;
  int indexEndSub3 = substr3.indexOf('"', indexStartSub3);
  String manufacturer = substr3.substring(indexStartSub3, indexEndSub3);

  int indexStartSub4 = substr4.indexOf(':') + 2;
  int indexEndSub4 = substr4.indexOf('"', indexStartSub4);
  String modelName = substr4.substring(indexStartSub4, indexEndSub4);

  int indexStartSub5 = substr5.indexOf(':') + 2;
  int indexEndSub5 = substr5.indexOf('"', indexStartSub5);
  String machineType = substr5.substring(indexStartSub5, indexEndSub5);
  
  Serial.println("xxxxxxxxxxxxxxxxxxxx");
  Serial.println(programName);
  Serial.println(runTime);
  Serial.println(manufacturer);
  Serial.println(modelName);
  Serial.println(machineType);
  Serial.println("xxxxxxxxxxxxxxxxxxxx");

  String output = String(programName) + "," + String(runTime) + "," + String(machineType);
  Serial.println(output);
  return output;
}
