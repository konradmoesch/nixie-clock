#ifndef NIXIE_CLOCK_TIMEPROVIDER_H
#define NIXIE_CLOCK_TIMEPROVIDER_H

#include "Arduino.h"
#include "types.hpp"
#include "ArduinoLog.h"
#include "InformationProvider.h"

class TimeProvider : public InformationProvider {
public:
    NixieValues_t getValues() override;
};


#endif //NIXIE_CLOCK_TIMEPROVIDER_H
