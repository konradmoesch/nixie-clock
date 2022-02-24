#ifndef IOController_hpp
#define IOController_hpp

#include "Arduino.h"
#include "types.hpp"
#include "NixieController.hpp"
#include <ArduinoLog.h>
#include <OneButton.h>

class IOController {
public:
    void initialize();

    void step();

private:
    OneButton button1;
};


#endif //IOController_hpp
