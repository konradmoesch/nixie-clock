/*
  StorageController.hpp - Library for managing ESP32 Preferences.
*/
#ifndef StorageController_hpp
#define StorageController_hpp

#include "Arduino.h"
#include "ArduinoLog.h"
#include "types.hpp"
#include <Preferences.h>

class StorageController {
public:
    static void initialize();

    static Timezone_t getTimezoneConfig();

    static void storeTimezoneConfig(Timezone_t timezoneConfig);

private:
};

#endif
