#include "Arduino.h"
#include "ArduinoLog.h"
#include "StorageController.hpp"
#include "WiFiController.hpp"
#include "TimeController.hpp"
#include "NixieController.hpp"
#include "SerialController.hpp"
//#include "LcdController.hpp"
#include "config.hpp"

StorageController storage_controller;
TimeController time_controller;
WiFiController wifi_controller;
SerialController serial_controller;
//LcdController lcd_controller;
NixieController nixie_controller;

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
    serial_controller.begin(115200, WiFiController::getAsyncServer());
    Log.begin(LOG_LEVEL_VERBOSE, &serial_controller, true);
    Log.noticeln("Starting Nixie-Clock");
    nixie_controller.togglePowerSupply();

    pinMode(36, INPUT);

    StorageController::initialize();
    WiFiController::initialize(nixie_controller);
    Timezone_t timezone = StorageController::getTimezoneConfig();
    TimeController::initialize(timezone);
    NixieController::initialize();
    //LcdController::initialize();
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
    //Serial.print("loop running on core");
    //Serial.println(xPortGetCoreID());
    WiFiController::step();

    currentState = digitalRead(36);
    if(lastState == LOW && currentState == HIGH)
        nixie_controller.togglePowerSupply();

    lastState = currentState;

    Log.noticeln(("Time: " + TimeController::getShortLocalTime()).c_str());
    //LcdController::setOutput(String(TimeController::getShortLocalTime()));
    delay(1000);
}
