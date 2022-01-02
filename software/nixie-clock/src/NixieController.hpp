/*
  NixieController.hpp - Library for controlling nixies.
*/
#ifndef NixieController_hpp
#define NixieController_hpp

#include "Arduino.h"

class NixieController {
  public:
    static void initialize();
    static void displayDigit(int anode, int digit);
};

#endif
