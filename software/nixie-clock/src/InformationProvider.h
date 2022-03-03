#ifndef NIXIE_CLOCK_INFORMATIONPROVIDER_H
#define NIXIE_CLOCK_INFORMATIONPROVIDER_H

#include "types.hpp"
#include "Arduino.h"

class InformationProvider {
public:
    virtual NixieValues_t getValues()=0;
    virtual ~InformationProvider()=default;
};

#endif //NIXIE_CLOCK_INFORMATIONPROVIDER_H
