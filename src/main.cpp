#include <Arduino.h>
#include "Config.hpp"
#include "OledPrint.hpp"
#include "Fonts.hpp"

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <Adafruit_SHT31.h>

// OLED 分辨率
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
Adafruit_SHT31 sht31;

void setup()
{
    Serial.begin(115200);
    sht31.begin();

    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
    {
        Serial.println(F("OLED 初始化失败！"));
        while (1);
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(F("正在尝试连接 WiFi ......"));
        print_init_info(1, oled);
        delay(1000);
    }
    Serial.println(F("连接 WiFi 成功"));
    print_init_info(2, oled);
    delay(1000);

    Serial.println(F("正在同步时间......"));
    print_init_info(3, oled);
    configTime(gmt_offset, daylight_offset, ntp_address);
    delay(5000);
    Serial.println(F("同步时间成功"));
    print_init_info(4, oled);

    Serial.println(F("关闭 WiFi"));
    WiFi.mode(WIFI_OFF);
}

void loop()
{
    static struct tm time_info;
    static float temperature, humidity;

    if (!getLocalTime(&time_info))
    {
        Serial.println(F("获取时间失败！"));
        return;
    }

    temperature = sht31.readTemperature();
    humidity = sht31.readHumidity();

    oled.clearDisplay();

    print_date(time_info.tm_year + 1900, time_info.tm_mon + 1, time_info.tm_mday, oled);
    print_week(time_info.tm_wday, oled);
    print_time(time_info.tm_hour, time_info.tm_min, time_info.tm_sec, oled);
    print_temp_humi(temperature, humidity, oled);

    oled.display();

    // 00:00:00 重启，间接实现定时同步时间
    if (0 == time_info.tm_hour && 0 == time_info.tm_min && 0 <= time_info.tm_sec && 3 >= time_info.tm_sec)
    {
        Serial.println(F("重启"));
        ESP.restart();
    }

    delay(1000);
}

