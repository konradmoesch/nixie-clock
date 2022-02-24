#include "IOController.hpp"

#define INPUT1 36

void printLongPress(){
    Serial.println("Long press");
}
void printSinglePress(){
    Serial.println("Single press");
}
void printDoublePress(){
    Serial.println("Double press");
}

void IOController::initialize(){
    button1 = OneButton(INPUT1, true);
    button1.attachLongPressStop(printLongPress);
    button1.attachClick(printSinglePress);
    button1.attachDoubleClick(printDoublePress);

    Log.noticeln("Initializing I/O");
    pinMode(INPUT1, INPUT);
}

void IOController::step() {
    button1.tick();
}
