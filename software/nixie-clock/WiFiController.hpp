/*
  WiFiController.hpp - Library for managing WiFi.
*/
#ifndef WiFiController_hpp
#define WiFiController_hpp

#include "Arduino.h"
#include <WiFi.h>

class WiFiController {
  public:
    void initialize(const char* ssid, const char* password);
};


#endif
