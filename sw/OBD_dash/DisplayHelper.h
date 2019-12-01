#ifndef DisplayHelper_h
#define DisplayHelper_h

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C
#define SHIFT_UP_RPM 2000

class DisplayHelper {
  public:
    DisplayHelper();
    void init();
    void drawLogo();
    void setInverted(bool mode);
    void showRpm(int rpm);
    void showBatteryVolts(String v);
    void showIntakeTemperature(byte temp);
    void showCoolantTemperature(int temp);
    void showTimingAdvance(int adv);
    void showMap(int map);
    void showTps(int tps);
    void showError(byte cod);
  private :
    bool displayInverted;
    SSD1306AsciiWire ssd1306;
    String getPadded(int num);
};

#endif
