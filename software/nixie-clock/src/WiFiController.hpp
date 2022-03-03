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
#include "InformationProxy.hpp"

#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <AutoConnect.h>

class WiFiController {
public:
    explicit WiFiController(InformationProxy* proxy);
    void initialize(NixieController);

    void step();

    AsyncWebServer &getAsyncServer();

private:
    AutoConnect _portal;
    AutoConnectConfig _autoConnectConfig;
    //WebServer webServer;
    AsyncWebServer _asyncWebServer;
    InformationProxy* _informationProxy;

};


#endif
