#include <ArduinoLog.h>
#include "WiFiController.hpp"
#include "TimeController.hpp"
#include "NixieController.hpp"

//WiFiServer server(80);

/*String header;

size_t currentTime = millis();
size_t previousTime = 0;*/

TimeController time_controller;
WiFiController wifi_controller;
NixieController nixie_controller;

void setup() {
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.noticeln("Starting Nixie-Clock");

  wifi_controller.initialize("ssid","password");
  time_controller.initialize("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org"); // Europe/Berlin
  nixie_controller.initialize();
  
  //server.begin();
}

void loop() {
  Serial.println(time_controller.getShortLocalTime());
  delay(random(500,2000));

}
