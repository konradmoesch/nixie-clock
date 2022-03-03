#ifndef NIXIE_CLOCK_YEARPROVIDER_HPP
#define NIXIE_CLOCK_YEARPROVIDER_HPP

#include "Arduino.h"
#include "types.hpp"
#include "ArduinoLog.h"
#include "InformationProvider.h"

class YearProvider : public InformationProvider {
public:
    NixieValues_t getValues() override;
};


#endif //NIXIE_CLOCK_YEARPROVIDER_HPP
