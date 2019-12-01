#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "DisplayHelper.h"
#include "vw_logo.h"

DisplayHelper::DisplayHelper() {
  displayInverted = false;
}

void DisplayHelper::init() {  
  Wire.begin();
  Wire.setClock(400000L);
  ssd1306.begin(&Adafruit128x64, I2C_ADDRESS);
  ssd1306.setContrast(255);

  ssd1306.ssd1306WriteCmd(SSD1306_SETPRECHARGE);
  ssd1306.ssd1306WriteCmd(0);

  ssd1306.ssd1306WriteCmd(SSD1306_SETVCOMDETECT);
  ssd1306.ssd1306WriteCmd(0);
}

void DisplayHelper::drawLogo() {
  byte r = 0; // Start row - Modify as needed
  byte c = 32; // Start col - Modify as needed
  int a = 0; // Position in array - Don't change - an array larger than 256 will need to use "int = a"
  for (byte b = 0; b < 8; b++) {
    ssd1306.setCursor (c,(r+b)); 
    for (byte i = 0; i < 64; i++) {
      ssd1306.ssd1306WriteRam(pgm_read_byte(&vw_logo[a]));
      a++;
    }  
  }
}

void DisplayHelper::setInverted(bool mode) {  
  if (mode != displayInverted) {
    displayInverted = mode;
    ssd1306.invertDisplay(displayInverted);
  }
}

void DisplayHelper::showRpm(int rpm) {
  if (rpm > SHIFT_UP_RPM) {
    setInverted(true);
  } else {
    setInverted(false);
  }
  
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("RPM      ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(rpm));
}

void DisplayHelper::showBatteryVolts(String v) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("TENSAO  ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(v);
}

void DisplayHelper::showIntakeTemperature(byte temp) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("TEMP ADM");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(temp));
}

void DisplayHelper::showCoolantTemperature(int temp) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("TEMP    ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(temp));  
}

void DisplayHelper::showTimingAdvance(int adv) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("PONTO   ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(adv)); 
}

void DisplayHelper::showMap(int map) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("MAP     ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(map)); 
}

void DisplayHelper::showTps(int tps) {
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.println("TPS     ");      
  ssd1306.setFont(lcdnums14x24);  
  ssd1306.print(getPadded(tps)); 
}

//TODO fazer com que este cara tenha um comprimento configurável!
String DisplayHelper::getPadded(int num) {
  bool negative = false;
  if (num < 0) {
    negative = true;
    num = num * -1;
  }

  char buff[5];
  char padded[6];
  
  //sprintf function will convert the long to a string
  sprintf(buff, "%.4u", num); // buff will be "01238"

  if (negative)
    padded[0] = '-';
  else
    padded[0] = buff[0];
  
  padded[1] = buff[1];
  padded[2] = buff[2];
  padded[3] = buff[3];
  padded[4] = buff[4];
  padded[5] = '\0'; // The terminating NULL

  return String(padded);
}

void DisplayHelper::showError(byte cod) {
  char str[5];
  sprintf(str, "%d", cod);
  
  setInverted(false);
  ssd1306.setCursor(0, 0);
  ssd1306.setFont(Adafruit5x7);
  ssd1306.set2X();
  ssd1306.print("Falha: ");  
  ssd1306.print(str);  
}
