#ifndef NIXIE_CLOCK_LCDCONTROLLER_HPP
#define NIXIE_CLOCK_LCDCONTROLLER_HPP

#include "Arduino.h"

class LcdController {
public:
    static void initialize();
    static void setOutput(const String& text);
};


#endif //NIXIE_CLOCK_LCDCONTROLLER_HPP
