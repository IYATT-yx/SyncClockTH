/**
 * @file      RtcModule.cpp
 * @brief     实时时钟模块
 * @author    IYATT-yx
 * @copyright Copyright (c) 2026 IYATT-yx.
 *            Licensed under the MIT License. See LICENSE file in the project root for full license information.
 */
#include "Arduino.h"
#include "Ds1302.h"
#include "Config.hpp"
#include <time.h>

Ds1302 rtc(RST, CLK, DAT);

bool syncTimeEsp32ToRtc()
{
    time_t now_ts = time(nullptr);
    
    if (now_ts < 86400)
    {
        Serial.println(F("ERROR: ESP32 system time is invalid!"));
        return false;
    }

    struct tm time_info;
    gmtime_r(&now_ts, &time_info);

    Ds1302::DateTime dt;
    dt.year   = (time_info.tm_year + 1900) % 100; 
    dt.month  = time_info.tm_mon + 1; 
    dt.day    = time_info.tm_mday;
    dt.hour   = time_info.tm_hour;
    dt.minute = time_info.tm_min;
    dt.second = time_info.tm_sec;

    if (time_info.tm_wday == 0)
    {
        dt.dow = 7;
    }
    else
    {
        dt.dow = time_info.tm_wday;
    }

    rtc.setDateTime(&dt);

    Serial.printf("SUCCESS: Wrote UTC 0 Time to DS1302 -> 20%02d-%02d-%02d %02d:%02d:%02d\n", dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
    return true;
}

bool syncTimeRtcToEsp32()
{
    rtc.init();
    if (rtc.isHalted())
    {
        Serial.println(F("WARNING: DS1302 is not running."));
        return false;
    }

    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    if (now.month == 0 || now.day == 0 || now.month > 12 || now.day > 31)
    {
        Serial.println(F("ERROR: RTC reports invalid zero date."));
        return false;
    }

    struct tm time_info;
    time_info.tm_year = (2000 + now.year) - 1900; 
    time_info.tm_mon  = now.month - 1;
    time_info.tm_mday = now.day;
    time_info.tm_hour = now.hour;
    time_info.tm_min  = now.minute;
    time_info.tm_sec  = now.second;
    time_info.tm_isdst = 0;

    char* old_tz = getenv("TZ");
    String saved_tz = old_tz ? old_tz : "";

    setenv("TZ", "UTC0", 1);
    tzset();

    time_t t = mktime(&time_info);
    if (!saved_tz.isEmpty())
    {
        setenv("TZ", saved_tz.c_str(), 1);
    }
    else
    {
        unsetenv("TZ");
    }
    tzset();

    if (t == (time_t)-1)
    {
        Serial.println(F("ERROR: mktime failed to convert RTC time."));
        return false;
    }

    struct timeval tv = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&tv, nullptr);

    Serial.printf("SUCCESS: Synced ESP32 from RTC (UTC 0) -> 20%02d-%02d-%02d %02d:%02d:%02d\n", now.year, now.month, now.day, now.hour, now.minute, now.second);
    return true;
}