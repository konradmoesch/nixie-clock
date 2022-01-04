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
    prefs.putString("VALID", "valid");
    prefs.end();
}

bool validTZConfig() {
    prefs.begin(PREFS_NAMESPACE, true);
    String value = prefs.getString("VALID");
    prefs.end();
    return value=="valid";
}

void StorageController::initialize() {
    Log.noticeln("Initializing Storage");
    if (!validTZConfig()) {
        Log.warningln("invalid Config. Setting default values");
        storeTimezoneConfig({"Europe/London","europe.pool.ntp.org",0});
    } else {
        Log.noticeln("Valid config");
    }
}
