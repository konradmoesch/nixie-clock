/*
  WiFiController.hpp - Library for managing Wi-Fi.
*/
#ifndef WiFiController_hpp
#define WiFiController_hpp

#include "Arduino.h"
#include "ArduinoLog.h"
#include "config.hpp"
#include "types.hpp"

#include "NixieController.hpp"
#include "TimeController.hpp"
#include "StorageController.hpp"

#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <AutoConnect.h>

class WiFiController {
public:
    WiFiController();
    void initialize(NixieController);

    static void step();

    AsyncWebServer &getAsyncServer();

private:
    WebServer webServer;
    AsyncWebServer asyncWebServer;
};


#endif
