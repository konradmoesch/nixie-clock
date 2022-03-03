#include "StorageController.hpp"

const char *PREFS_NAMESPACE = "NTP";
const char *PREFS_KEY = "NTP";

Timezone_t StorageController::getTimezoneConfig() {
    Preferences prefs;
    Timezone_t timezoneConfig;
    prefs.begin(PREFS_NAMESPACE, true);
    prefs.getBytes(PREFS_KEY, &timezoneConfig, sizeof(Timezone_t));
    prefs.end();
    Serial.println("Read tz config:");
    Serial.println(timezoneConfig.zone);
    return timezoneConfig;
}

void StorageController::storeTimezoneConfig(Timezone_t timezoneConfig) {
    Preferences prefs;
    prefs.begin(PREFS_NAMESPACE);
    prefs.putBytes(PREFS_KEY, &timezoneConfig, sizeof(Timezone_t));
    prefs.putString("VALID", "valid");
    prefs.end();
}

bool validTZConfig() {
    Preferences prefs;
    prefs.begin(PREFS_NAMESPACE, true);
    String value = prefs.getString("VALID");
    prefs.end();
    return value=="valid";
}

void StorageController::initialize() {
    Log.noticeln("Initializing Storage");
    if (!validTZConfig()) {
        Log.warningln("invalid Config. Setting default values");
        storeTimezoneConfig({"Europe/Berlin","europe.pool.ntp.org",1});
    } else {
        Log.noticeln("Valid config");
    }
}
