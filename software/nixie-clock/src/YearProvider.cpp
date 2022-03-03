#include "YearProvider.hpp"

NixieValues_t YearProvider::getValues() {
    NixieValues_t nixieValues;
    struct tm timeinfo{};
    if (!getLocalTime(&timeinfo)) {
        Log.errorln("Failed to obtain time");
    }
    int year = 1900 + timeinfo.tm_year;
    nixieValues.nixie6 = year % 10;
    nixieValues.nixie5 = (year / 10) % 10;
    nixieValues.nixie4 = (year / 100) % 10;
    nixieValues.nixie3 = (year / 1000);
    nixieValues.nixie2 = 10;
    nixieValues.nixie1 = 10;

    return nixieValues;
}
