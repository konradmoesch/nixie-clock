#include "CathodePoisoningPreventionProvider.hpp"

NixieValues_t CathodePoisoningPreventionProvider::getValues() {
    delay(300);
    NixieValues_t nixieValues;
    nixieValues.nixie1 = _currentDigit;
    nixieValues.nixie2 = _currentDigit;
    nixieValues.nixie3 = _currentDigit;
    nixieValues.nixie4 = _currentDigit;
    nixieValues.nixie5 = _currentDigit;
    nixieValues.nixie6 = _currentDigit;
    _currentDigit++;
    if (_currentDigit>9) _currentDigit = 0;
    return nixieValues;
}
