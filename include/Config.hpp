/**
 * 配置文件
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

// WiFi
// 注意只支持 2.4GHz 频段
const char PROGMEM ssid[] = "IYATT-yx_2.4GHz";
const char PROGMEM password[] = "wifi5five";

// NTP 服务器地址
const char PROGMEM ntp_address1[] = "ntp.aliyun.com"; // 阿里云
const char PROGMEM ntp_address2[] = "ntp.tencent.com"; // 腾讯云
const char PROGMEM ntp_address3[] = "ntp.ntsc.ac.cn"; // 中国国家授时中心

// 时区
const int gmt_offset = 8 * 60 * 60; // UTC/GMT+8，东 8 时区偏移量，单位秒
const int daylight_offset = 0; // 夏令时偏移值，单位

// OLED 参数
#define OLED_ADDRESS    0x3C // IIC 地址
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

// 实时时钟模块引脚
#define CLK     14
#define DAT     13
#define RST     27

#endif