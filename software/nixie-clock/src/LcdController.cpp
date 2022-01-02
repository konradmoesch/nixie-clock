#include "Arduino.h"
#include "LcdController.hpp"
#include "ArduinoLog.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void LcdController::initialize() {
    Log.noticeln("Starting LCD Controller");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello World!");
}

void LcdController::setOutput(const String& text) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print(text);
}