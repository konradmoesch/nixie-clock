#ifndef NIXIE_CLOCK_DATEPROVIDER_HPP
#define NIXIE_CLOCK_DATEPROVIDER_HPP

#include "Arduino.h"
#include "types.hpp"
#include "ArduinoLog.h"
#include "InformationProvider.h"

class DateProvider : public InformationProvider {
public:
    NixieValues_t getValues() override;
};


#endif //NIXIE_CLOCK_DATEPROVIDER_HPP
