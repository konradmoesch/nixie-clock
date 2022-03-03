#ifndef NIXIE_CLOCK_INFORMATIONPROXY_HPP
#define NIXIE_CLOCK_INFORMATIONPROXY_HPP

#include "Arduino.h"
#include "types.hpp"
#include "ArduinoLog.h"
#include "InformationProvider.h"
#include "NixieController.hpp"
#include "TimeProvider.h"
#include "DateProvider.hpp"
#include "YearProvider.hpp"
#include "CathodePoisoningPreventionProvider.hpp"

class InformationProxy {
public:
    explicit InformationProxy(NixieController* nixieController);
    ~InformationProxy();
    void setProvider(int providerId);
    void nextProvider();
    void step();
    void toggleNixiePower();
    void toggleNixiePoison();
private:
    NixieController* _nixieController;
    InformationProvider* _providers[4]{};
    int _currentProvider;
};


#endif //NIXIE_CLOCK_INFORMATIONPROXY_HPP
