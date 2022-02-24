#ifndef NIXIE_CLOCK_LCDCONTROLLER_HPP
#define NIXIE_CLOCK_LCDCONTROLLER_HPP

#include "Arduino.h"
#include "ArduinoLog.h"
#include <LiquidCrystal_I2C.h>

class LcdController {
public:
    void initialize();

    void setOutput(const String &text);

private:
    LiquidCrystal_I2C lcd;
};


#endif //NIXIE_CLOCK_LCDCONTROLLER_HPP
