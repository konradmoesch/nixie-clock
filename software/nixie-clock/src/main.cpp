#include "Arduino.h"
#include "ArduinoLog.h"
#include "StorageController.hpp"
#include "WiFiController.hpp"
#include "TimeController.hpp"
#include "NixieController.hpp"
#include "LcdController.hpp"
#include "config.hpp"

StorageController storage_controller;
TimeController time_controller;
WiFiController wifi_controller;
LcdController lcd_controller;
NixieController nixie_controller;

TaskHandle_t NixieTask;

[[noreturn]] void NixieLoop(void* parameter) {
    Serial.print("NixieLoop running on core");
    Serial.println(xPortGetCoreID());
    int currentTime[6];
    while (true) {
        TimeController::getTime(currentTime);
        NixieController::displayNumberString(currentTime);
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

// cppcheck-suppress unusedFunction
void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.noticeln("Starting Nixie-Clock");

  StorageController::initialize();
  WiFiController::initialize();
  Timezone_t timezone = StorageController::getTimezoneConfig();
  TimeController::initialize(timezone);
  NixieController::initialize();
  LcdController::initialize();
    xTaskCreatePinnedToCore(
            NixieLoop,
            "NixieTask",
            10000,
            nullptr,
            0,
            &NixieTask,
            0);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// cppcheck-suppress unusedFunction
void loop() {
    Serial.print("loop running on core");
    Serial.println(xPortGetCoreID());
    WiFiController::step();
    Log.noticeln("Time:");
    Serial.println(TimeController::getShortLocalTime());
    LcdController::setOutput(String(TimeController::getShortLocalTime()));
    delay(1000);
}
