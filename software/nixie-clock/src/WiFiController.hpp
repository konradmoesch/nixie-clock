/*
  WiFiController.hpp - Library for managing WiFi.
*/
#ifndef WiFiController_hpp
#define WiFiController_hpp

#include "Arduino.h"
#include "types.hpp"

class WiFiController {
  public:
    static void initialize();
    static void step();
};


#endif
