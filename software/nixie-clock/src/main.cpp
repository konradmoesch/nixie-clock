#include "Arduino.h"
#include "ArduinoLog.h"
#include "StorageController.hpp"
#include "WiFiController.hpp"
#include "TimeController.hpp"
#include "NixieController.hpp"
#include "SerialController.hpp"
#include "IOController.hpp"
#if USE_LCD
#include "LcdController.hpp"
#endif
#include "config.hpp"

StorageController storage_controller;
TimeController time_controller;
WiFiController wifi_controller;
SerialController serial_controller;
#if USE_LCD
LcdController lcd_controller;
#endif
NixieController nixie_controller;
IOController io_controller;

TaskHandle_t NixieTask;

[[noreturn]] void NixieLoop(void *parameter) {
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
    serial_controller.begin(115200, wifi_controller.getAsyncServer());
    Log.begin(LOG_LEVEL_VERBOSE, &serial_controller, true);
    Log.noticeln("Starting Nixie-Clock");
    nixie_controller.togglePowerSupply();

    StorageController::initialize();
    wifi_controller.initialize(nixie_controller);
    Timezone_t timezone = StorageController::getTimezoneConfig();
    TimeController::initialize(timezone);
    nixie_controller.initialize();
    io_controller.initialize();
#if USE_LCD
    LcdController::initialize();
#endif

    xTaskCreatePinnedToCore(
            NixieLoop,
            "NixieTask",
            10000,
            nullptr,
            0,
            &NixieTask,
            0);
    Log.noticeln("Initialization finished");
}

int lastState = HIGH;
int currentState;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// cppcheck-suppress unusedFunction
void loop() {
    WiFiController::step();

    currentState = digitalRead(36);
    if (lastState == LOW && currentState == HIGH)
        nixie_controller.togglePowerSupply();

    lastState = currentState;

    Log.noticeln(("Time: " + TimeController::getShortLocalTime()).c_str());
    io_controller.step();
#if USE_LCD
    LcdController::setOutput(String(TimeController::getShortLocalTime()));
#endif
    delay(1000);
}
