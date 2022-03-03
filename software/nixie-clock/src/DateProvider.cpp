#include "DateProvider.hpp"

NixieValues_t DateProvider::getValues() {
    NixieValues_t nixieValues;
    struct tm timeinfo{};
    if (!getLocalTime(&timeinfo)) {
        Log.errorln("Failed to obtain time");
    }
    int month = timeinfo.tm_mon + 1;
    nixieValues.nixie2 = timeinfo.tm_mday % 10;
    nixieValues.nixie1 = (timeinfo.tm_mday - nixieValues.nixie2) / 10;
    nixieValues.nixie3 = 10;
    nixieValues.nixie5 = month % 10;
    nixieValues.nixie4 = (month - nixieValues.nixie5) / 10;
    nixieValues.nixie6 = 10;

    return nixieValues;
}
