/*
  StorageController.hpp - Library for managing ESP32 Preferences.
*/
#ifndef StorageController_hpp
#define StorageController_hpp

#include "Arduino.h"
#include "types.hpp"

class StorageController {
public:
    static void initialize();
    static Timezone_t getTimezoneConfig();
    static void storeTimezoneConfig(Timezone_t timezoneConfig);
};

#endif