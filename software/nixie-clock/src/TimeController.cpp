#include "Arduino.h"
#include "TimeController.hpp"
#include "types.hpp"
#include <ArduinoLog.h>

void TimeController::setTimezone(const Timezone_t &timezone) {
    Log.noticeln("Setting Timezone to %s\n", timezone.zone);
    configTime(timezone.tzoff * 3600, 0, timezone.ntpServer);
}

void TimeController::initialize(const Timezone_t &timezone) {
    Log.noticeln("Initializing NTP");
    struct tm timeinfo{};
    setTimezone(timezone);
    if (!getLocalTime(&timeinfo)) {
        Log.warningln("Failed to obtain time");
        return;
    }
    Log.noticeln("Got the time from NTP");
}

String TimeController::getShortLocalTime() {
    struct tm timeinfo{};
    char timeNow[] = "00:00:00"; //size: 9
    if (!getLocalTime(&timeinfo)) {
        Log.errorln("Failed to obtain time");
        return "";
    }
    strftime(timeNow, 9, "%H:%M:%S", &timeinfo);
    return timeNow;
}

void TimeController::getTime(int time[6]) {
    struct tm timeinfo{};
    if (!getLocalTime(&timeinfo)) {
        Log.errorln("Failed to obtain time");
    }
    time[1]=timeinfo.tm_hour%10;
    time[0]=(timeinfo.tm_hour-time[1])/10;
    time[3]=timeinfo.tm_min%10;
    time[2]=(timeinfo.tm_min-time[3])/10;
    time[5]=timeinfo.tm_sec%10;
    time[4]=(timeinfo.tm_sec-time[5])/10;
}

String TimeController::getLongTime() {
    static const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
    struct tm *tm;
    time_t t;
    char dateTime[26];

    t = time(nullptr);
    tm = localtime(&t);
    sprintf(dateTime, "%04d/%02d/%02d(%s) %02d:%02d:%02d.",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            wd[tm->tm_wday],
            tm->tm_hour, tm->tm_min, tm->tm_sec);
    return dateTime;
}
