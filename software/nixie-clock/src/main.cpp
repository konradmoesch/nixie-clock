#include "Arduino.h"
#include "ArduinoLog.h"
#include "StorageController.hpp"
#include "WiFiController.hpp"
#include "TimeController.hpp"
#include "NixieController.hpp"
#include "SerialController.hpp"
#include "IOController.hpp"
#include "InformationProxy.hpp"

#if USE_LCD
#include "LcdController.hpp"
#endif

#include "config.hpp"

StorageController storage_controller;
TimeController time_controller;
SerialController serial_controller;
#if USE_LCD
LcdController lcd_controller;
#endif
NixieController nixie_controller;
InformationProxy information_proxy(&nixie_controller);
WiFiController wifi_controller(&information_proxy);
IOController io_controller(&information_proxy);

TaskHandle_t SecondTask;

[[noreturn]] void NixieLoop(void *parameter) {
    while (true) {
        nixie_controller.displayValues();
    }
}

[[noreturn]] void ControlLoop(void *parameter) {
    while (true) {
        wifi_controller.step();
        information_proxy.step();
        io_controller.step();
        //Log.noticeln(("Time: " + TimeController::getShortLocalTime()).c_str());
#if USE_LCD
        LcdController::setOutput(String(TimeController::getShortLocalTime()));
#endif
        delay(10);
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
            "SecondTask",
            10000,
            nullptr,
            0,
            &SecondTask,
            0);
    Log.noticeln("Initialization finished");
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// cppcheck-suppress unusedFunction
void loop() {
    ControlLoop(nullptr);
}
