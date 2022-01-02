/*
  TimeController.hpp - Library for managing NTP.
*/
#ifndef TimeController_hpp
#define TimeController_hpp

#include "Arduino.h"
#include "types.hpp"

class TimeController {
public:
    static void initialize(const Timezone_t& timezone);
    static String getShortLocalTime();
    static String getLongTime();

    static void setTimezone(const Timezone_t &timezone);
};

#endif
