#include "Arduino.h"
#include "ArduinoLog.h"
#include "StorageController.hpp"
#include "WiFiController.hpp"
#include "TimeController.hpp"
//#include "NixieController.hpp"
#include "LcdController.hpp"
#include "config.hpp"

StorageController storage_controller;
TimeController time_controller;
WiFiController wifi_controller;
LcdController lcd_controller;
//NixieController nixie_controller;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.noticeln("Starting Nixie-Clock");

  WiFiController::initialize();
  Timezone_t timezone = StorageController::getTimezoneConfig();
  TimeController::initialize(timezone);
  //nixie_controller.initialize();
  LcdController::initialize();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// cppcheck-suppress unusedFunction
void loop() {
    WiFiController::step();
    Log.noticeln("Time:");
    Serial.println(String(TimeController::getShortLocalTime()));
    LcdController::setOutput(String(TimeController::getShortLocalTime()));
    delay(1000);
}
