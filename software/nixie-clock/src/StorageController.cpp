#include <Preferences.h>
#include "ArduinoLog.h"
#include "Arduino.h"
#include "StorageController.hpp"

const char *PREFS_NAMESPACE = "NTP";
const char *PREFS_KEY = "NTP";
Preferences prefs;

Timezone_t StorageController::getTimezoneConfig() {
    Timezone_t timezoneConfig;
    prefs.begin(PREFS_NAMESPACE, true);
    prefs.getBytes(PREFS_KEY, &timezoneConfig, sizeof(Timezone_t));
    prefs.end();
    Serial.println("Read tz config:");
    Serial.println(timezoneConfig.zone);
    return timezoneConfig;
}

void StorageController::storeTimezoneConfig(Timezone_t timezoneConfig) {
    prefs.begin(PREFS_NAMESPACE);
    prefs.putBytes(PREFS_KEY, &timezoneConfig, sizeof(Timezone_t));
    prefs.end();
}

void StorageController::initialize() {
    Log.noticeln("Initializing Storage");
}