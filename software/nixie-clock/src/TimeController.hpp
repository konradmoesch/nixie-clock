/*
  TimeController.hpp - Library for managing NTP.
*/
#ifndef TimeController_hpp
#define TimeController_hpp

#include "Arduino.h"
#include <time.h>

class TimeController {
  public:
    void initialize(String timezone, const char* ntp_server);
    String getShortLocalTime();
    void printLocalTime();
};

#endif
