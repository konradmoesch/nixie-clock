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

    static void displayBCD(int anode, BinaryCodedDecimal_t binaryCodedDecimal);

    void displayValues();

    void setNixieValues(NixieValues_t nixieValues);

    void togglePowerSupply();

#if USE_DELIMITERS
    void toggleDelimiters();
#endif

private:
    PowerStatus powerStatus = OFF;
#if USE_DELIMITERS
    PowerStatus delimiterStatus = OFF;
#endif
    BinaryCodedDecimal_t bcdValues[6];
    BinaryCodedDecimal_t testBCD;
    bool testA;
    bool testB;
    bool testC;
    bool testD;
};

#endif
