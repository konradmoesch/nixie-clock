#include "Arduino.h"
#include "TimeController.hpp"
#include <ArduinoLog.h>

void setTimezone(String timezone){
  Log.noticeln("Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}

void TimeController::initialize(String timezone, const char* ntp_server){
  struct tm timeinfo;

  Log.noticeln("Initializing NTP");
  configTime(0, 0, ntp_server);    // First connect to NTP server, with 0 TZ offset
  if(!getLocalTime(&timeinfo)){
    Log.warningln("Failed to obtain time");
    return;
  }
  Log.noticeln("Got the time from NTP");
  setTimezone(timezone);
}

void TimeController::printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Log.warningln("Failed to obtain time 1");
    return;
  }
  Serial.println(&timeinfo, "current time: %A, %B %d %Y %H:%M:%S zone %Z %z ");
}

String TimeController::getShortLocalTime(){
  struct tm timeinfo;
  char timeNow[] = "00:00:00"; //size: 9
  if(!getLocalTime(&timeinfo)){
    Log.errorln("Failed to obtain time 1");
    return "";
  }
  strftime(timeNow, 9, "%H:%M:%S", &timeinfo);
  return timeNow;
}
