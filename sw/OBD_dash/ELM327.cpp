#include "ELM327.h"

byte ELM327::init() {
  Serial.begin(38400);
  
  Serial.print("ATD\r");
  delay(200);
  Serial.print("ATZ\r");
  delay(1000);

  byte result = readElmResponse();
  if (result != ELM_OK)
    return result;

  //if (strstr(buffer, "ELM327 v1.5") == NULL) 
  //  return ELM_RESET_FAIL;
  
  Serial.print("ATE0\r");
  delay(200);
  Serial.print("ATL0\r");
  delay(200);
  Serial.print("ATS0\r");
  delay(200);
  Serial.print("ATH0\r");
  delay(200);
  Serial.print("ATSP3\r");
  delay(200);
  
  Serial.print("0100\r");
  delay(1000);
  
  result = readElmResponse();

  return result;
}

String ELM327::getBatteryVolts() {
  Serial.print("ATRV\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    return String(buffer);
  }

  return "00.0";
}

int ELM327::getEngineTemperature() {
  Serial.print("0105\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = '\0';
  
    int value = (int)strtol(buffer, NULL, HEX_BASE);
  
    return value - 40;
  }
  
  return 0;
}

int ELM327::getRpm() {
  Serial.print("010C\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {  
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = buffer[6];
    buffer[3] = buffer[7];
    buffer[4] = '\0';

    int value = (int)strtol(buffer, NULL, HEX_BASE);

    return value / 4;
  }

  return 0;
}

int ELM327::getIntakeTemperature() {
  Serial.print("010F\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = '\0';
  
    int value = (int)strtol(buffer, NULL, HEX_BASE);
  
    return value - 40;
  }
  
  return 0;
}

int ELM327::getTimingAdvance() {
  Serial.print("010E\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = '\0';
  
    int value = (int)strtol(buffer, NULL, HEX_BASE);
  
    return value/2 - 64;
  }
  
  return 0;
}

int ELM327::getMap() {
  Serial.print("010B\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = '\0';
  
    int value = (int)strtol(buffer, NULL, HEX_BASE);
  
    return value;
  }
  
  return 0;
}

int ELM327::getTps() {
  Serial.print("0111\r");

  byte result = readElmResponse();
  if (result == ELM_OK) {
    buffer[0] = buffer[4];
    buffer[1] = buffer[5];
    buffer[2] = '\0';
  
    int value = (int)strtol(buffer, NULL, HEX_BASE);
  
    return (value * 100) / 255;
  }
  
  return 0;
}

byte ELM327::readElmResponse() {
  byte counter = 0;
  bool found = false;
  unsigned long timeOut = millis() + ELM_TIMEOUT_LIMIT;
  
  while (!found && millis() < timeOut) {
    if (Serial.available() > 0) {
      buffer[counter] = Serial.read();
      if (buffer[counter] == '>') {
        found = true;
        buffer[counter]='\0';
      } else if (buffer[counter] != '\r'){
        counter++;
      }
    }
  }
  
  if (found) {
    if (strcmp(buffer, "NO DATA") == 0) 
      return ELM_NO_DATA;
    else if (strcmp(buffer, "BUS INIT: ERROR") == 0) 
      return ELM_BUS_INIT_ERROR;
    else return ELM_OK;
  }

  if (millis() > timeOut) {
    return ELM_TIMEOUT;
  }


  return ELM_NO_RESPONSE;
}
