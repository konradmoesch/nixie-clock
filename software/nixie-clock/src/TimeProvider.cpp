#include "TimeProvider.h"

NixieValues_t TimeProvider::getValues() {
    NixieValues_t nixieValues;
    struct tm timeinfo{};
    if (!getLocalTime(&timeinfo)) {
        Log.errorln("Failed to obtain time");
    }
    nixieValues.nixie1 = (timeinfo.tm_hour / 10) % 10;
    nixieValues.nixie2 = timeinfo.tm_hour % 10;
    nixieValues.nixie3 = (timeinfo.tm_min / 10) % 10;
    nixieValues.nixie4 = timeinfo.tm_min % 10;
    nixieValues.nixie5 = (timeinfo.tm_sec / 10) % 10;
    nixieValues.nixie6 = timeinfo.tm_sec % 10;

    return nixieValues;
}
