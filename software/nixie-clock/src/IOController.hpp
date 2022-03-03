#ifndef IOController_hpp
#define IOController_hpp

#include "Arduino.h"
#include "types.hpp"
#include <ArduinoLog.h>
#include <OneButton.h>
#include "InformationProxy.hpp"

class IOController {
public:
    explicit IOController(InformationProxy* proxy);

    void initialize();

    void step();

private:
    OneButton _button;
    InformationProxy* _informationProxy;
};


#endif //IOController_hpp
