/**
 * 配置文件
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

// WiFi
const char PROGMEM ssid[] = "IYATT-yx_2.4GHz";
const char PROGMEM password[] = "wifi5five";

// NTP 服务器地址
const char PROGMEM ntp_address[] = "ntp.aliyun.com";

// 时区
const int gmt_offset = 8 * 60 * 60; // UTC/GMT+8，东 8 时区偏移量，单位秒
const int daylight_offset = 0; // 夏令时偏移值，单位

// OLED 参数
#define OLED_ADDRESS    0x3C // IIC 地址

#endif