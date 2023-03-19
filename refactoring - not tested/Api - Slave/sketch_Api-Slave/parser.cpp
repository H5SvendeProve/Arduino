#include "parser.h"

String httpRequsetPareser_StatusCode(String textToParse){
  int indexOfSpace = textToParse.indexOf(' ') + 1;
  int indexOfNewLine = textToParse.indexOf('\n');
  String substr = textToParse.substring(indexOfSpace, indexOfNewLine);

  return substr;
}

String httpRequsetPareser(String textToParse){
  int indexStart = textToParse.indexOf("\r\n\r\n") + 8;
  int indexEnd = textToParse.indexOf('\n', indexStart);
  String substr = textToParse.substring(indexStart, indexEnd);
  
  Serial.println("parser: httprequsetparser");
  return substr;
}

String pareseModule(String textToParse){
  int indexOfKoma1 = textToParse.indexOf(',') + 2;
  int indexOfKoma2 = textToParse.indexOf(',', indexOfKoma1) + 2;
  int indexOfKoma3 = textToParse.indexOf(',', indexOfKoma2) + 2;

  String substr1 = textToParse.substring(0, indexOfKoma1);
  String substr2 = textToParse.substring(indexOfKoma1, indexOfKoma2);
  String substr3 = textToParse.substring(indexOfKoma2, indexOfKoma3);
  String substr4 = textToParse.substring(indexOfKoma3);
  
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
  String machineType = substr4.substring(indexStartSub4, indexEndSub4);

  String output = String(programName) + "," + String(runTime) + "," + String(machineType);
  Serial.println(output);
  return output;
}
