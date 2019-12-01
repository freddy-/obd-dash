
#include <EEPROM.h>
#include "DisplayHelper.h"
#include "ELM327.h"
#include <stdlib.h>
#include <string.h>

#define BUTTON 2


int ADDR_PAGE_COUNTER = 0;

DisplayHelper display;
ELM327 elm327;
byte pageCounter = 0;
bool pageChanged = false;

void setup() {
  display.init();
  display.drawLogo();

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  byte elmStatus = elm327.init();
  if (elmStatus != ELM_OK) {
    finalizarComFalha(elmStatus);
  }
    
  pageCounter = EEPROM.read(ADDR_PAGE_COUNTER);
}

void readButtonState() {
  if (digitalRead(BUTTON) == LOW) {
    delay(100);
    pageCounter++;
    pageChanged = true;
    if (pageCounter > 6) {
      pageCounter = 0;
    }
    while (digitalRead(BUTTON) == LOW);
  }
}

void savePageChange() {
  if (pageChanged) {
     EEPROM.write(ADDR_PAGE_COUNTER, pageCounter);
  }
}

/*
 * 0 rpm
 * 1 bateria
 * 2 intake temp
 * 3 temperatura motor
 * 4 avanço de ponto
 * 5 MAP
 * 6 TPS
 */

void loop() {
  readButtonState();
  
  switch (pageCounter) {
    case 0:
      display.showRpm(elm327.getRpm());
      break;
    
    case 1:
      display.showBatteryVolts(elm327.getBatteryVolts());
      break;      
      
    case 2:
      display.showIntakeTemperature(elm327.getIntakeTemperature());
      break;
      
    case 3:
      display.showCoolantTemperature(elm327.getEngineTemperature());
      break;   

    case 4:
      display.showTimingAdvance(elm327.getTimingAdvance());
      break; 

    case 5:
      display.showMap(elm327.getMap());
      break; 

    case 6:
      display.showTps(elm327.getTps());
      break;
  } 
  
  savePageChange();
  pageChanged = false;
}

void finalizarComFalha(byte cod) {
  display.showError(cod);
  while(true);
}

void serial_flush_buffer() {
  while (Serial.available() > 0)
   Serial.read();
}
