/*
  NixieController.hpp - Library for controlling nixies.
*/
#ifndef NixieController_hpp
#define NixieController_hpp

#include "Arduino.h"
#include "ArduinoLog.h"
#include "types.hpp"
#include "config.hpp"

class NixieController {
public:
    void initialize();

    static void displayDigit(int anode, int digit);

    static void displayNumberString(int string[6]);

    void togglePowerSupply();

#if USE_DELIMITERS
    void toggleDelimiters();
#endif

private:
    PowerStatus powerStatus;
#if USE_DELIMITERS
    PowerStatus delimiterStatus;
#endif
};

#endif
