#ifndef NIXIE_CLOCK_CATHODEPOISONINGPREVENTIONPROVIDER_HPP
#define NIXIE_CLOCK_CATHODEPOISONINGPREVENTIONPROVIDER_HPP

#include "Arduino.h"
#include "InformationProvider.h"

class CathodePoisoningPreventionProvider: public InformationProvider {
    NixieValues_t getValues() override;
public:
    int _currentDigit = 0;
};


#endif //NIXIE_CLOCK_CATHODEPOISONINGPREVENTIONPROVIDER_HPP
