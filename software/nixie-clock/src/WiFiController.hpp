/*
  WiFiController.hpp - Library for managing WiFi.
*/
#ifndef WiFiController_hpp
#define WiFiController_hpp

#include "Arduino.h"
#include "types.hpp"
#include "NixieController.hpp"
#include <WebServer.h>
#include <ESPAsyncWebServer.h>

class WiFiController {
  public:
    static void initialize(NixieController);
    static void step();
    static AsyncWebServer& getAsyncServer();
};


#endif
