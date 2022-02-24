#include "LcdController.hpp"


void LcdController::initialize() {
    lcd = LiquidCrystal_I2C(0x27, 16, 2);
    Log.noticeln("Starting LCD Controller");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello World!");
}

void LcdController::setOutput(const String &text) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print(text);
}