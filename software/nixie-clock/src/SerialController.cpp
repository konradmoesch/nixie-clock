#include "SerialController.hpp"

SerialController::SerialController()= default;

void SerialController::begin(unsigned long baud, AsyncWebServer& asyncWebServer) {
    Serial.begin(baud);
    //WebSerial.begin(&asyncWebServer);
}

void SerialController::println(const String& message) {
    //WebSerial.println(message);
    Serial.println(message);
}
void SerialController::println(const char message[]) {
    //WebSerial.println(message);
    Serial.println(message);
}

void SerialController::print(const String& message) {
    //WebSerial.print(message);
    Serial.print(message);
}
void SerialController::print(const char message[]) {
    //WebSerial.print(message);
    Serial.print(message);
}

void webSerialWrite(uint8_t c) {
    auto c_char = reinterpret_cast<char *>(&c);
    if (c==10)
        WebSerial.println("");
    else WebSerial.print(c_char);
}
void webSerialWriteBuffer(const uint8_t *buffer, size_t size) {
    while (size--) {
        uint8_t buf_elem = (*buffer--);
        if (buf_elem==10)
            WebSerial.println("");
        else if (buf_elem==100)
            //todo improve this hack
            WebSerial.print(" ");
        else if (buf_elem==58)
            //todo improve this hack
            WebSerial.print(":");
        else Serial.println("unrecognized char: " + String(buf_elem));
    }
}

size_t SerialController::write(uint8_t c) {
    Serial.write( c);
    //webSerialWrite(c);
    return 1;
}

size_t SerialController::write(const uint8_t *buffer, size_t size) {
    //webSerialWriteBuffer(buffer, size);
    return Serial.write(buffer, size);
}
