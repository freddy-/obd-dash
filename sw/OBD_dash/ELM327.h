#include <Arduino.h>

#ifndef ELM327_h
#define ELM327_h

#define HEX_BASE 16

#define ELM_TIMEOUT_LIMIT 2000
#define ELM_OK 0
#define ELM_RESET_FAIL 1
#define ELM_NO_DATA 2
#define ELM_NO_RESPONSE 3
#define ELM_BUS_INIT_ERROR 4
#define ELM_TIMEOUT 5

class ELM327 {
  public:
    byte init();
    int getRpm();
    String getBatteryVolts();
    int getIntakeTemperature();
    int getEngineTemperature();
    int getTimingAdvance();
    int getMap();
    int getTps();

   private:
    char buffer[64];

    byte readElmResponse();
};


#endif
