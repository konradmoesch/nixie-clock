#ifndef SerialController_hpp
#define SerialController_hpp

#include "Arduino.h"
#include "WiFiController.hpp"
#include "WebSerial.h"

class SerialController: public Stream {
public:
    SerialController();

    void begin(unsigned long baud, AsyncWebServer& asyncWebServer);

    void println(const String &message);
    void println(const char message[]);

    void print(const String &message);
    void print(const char message[]);


    int peek() {
        if (available()) {
            return Serial.peek();
        }
        return -1;
    }

    int read() {
        if (available()) {
            return Serial.read();
        }
        return -1;
    }
    size_t read(uint8_t *buffer, size_t size) {
        size_t avail = available();
        if (size < avail) {
            avail = size;
        }
        size_t count = 0;
        while(count < avail) {
            *buffer++ = Serial.read();
            count++;
        }
        return count;
    }

    inline size_t read(char * buffer, size_t size)
    {
        return read((uint8_t*) buffer, size);
    }
    void flush() {
        Serial.flush();
    }

    void flush(bool txOnly) {
        Serial.flush(txOnly);
    }

    int available() {
        return Serial.available();
    }
    size_t write(uint8_t c);

    size_t write(const uint8_t *buffer, size_t size);

    inline size_t write(const char * buffer, size_t size)
    {
        return write((uint8_t*) buffer, size);
    }
    inline size_t write(const char * s)
    {
        return write((uint8_t*) s, strlen(s));
    }
    inline size_t write(unsigned long n)
    {
        return write((uint8_t) n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t) n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t) n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t) n);
    }
};


#endif //SerialController_hpp
