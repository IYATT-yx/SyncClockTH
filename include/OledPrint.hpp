#ifndef OLEDPRINT_HPP
#define OLEDPRINT_HPP

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

/**
 * 显示数字或字母
 * @param row 坐标行数，可取 0~15
 * @param col 坐标列数，可取 0~3
 * @param font 字模
 * @param oled OLED 对象
 */
void display_num_let(byte row, byte col, const unsigned char font[16], Adafruit_SSD1306 & oled);

/**
 * 显示汉字
 * @param row 坐标行数，可取 0~7
 * @param col 坐标列数，可取 0~3
 * @param font 字模
 * @param oled OLED 对象
 */
void display_chinese(byte row, byte col, const unsigned char font[32], Adafruit_SSD1306 & oled);

/**
 * 显示星期
 * @param week 星期数，0~7对应星期日、星期一......星期六
 * @param oled OLED 对象
 */
void print_week(byte week, Adafruit_SSD1306 & oled);

/**
 * 显示初始化信息
 * @param step  1 正在连接WiFi
 *              2 连接WiFi成功
 *              3 正在同步时间
 *              4 同步时间成功
 * @param oled OLED 对象
 */
void print_init_info(byte step, Adafruit_SSD1306 & oled);

/**
 * 显示日期
 * @param year 年份
 * @param mon 月份
 * @param day 日
 * @param oled OLED 对象
 */
void print_date(int year, byte mon, byte day, Adafruit_SSD1306 & oled);

/**
 * 显示时间
 * @param hour 小时
 * @param min 分钟
 * @param sec 秒
 * @param oled OLED 对象
 */
void print_time(byte hour, byte min, byte sec, Adafruit_SSD1306 & oled);

/**
 * 显示温湿度
 * @param temperature 温度
 * @param humidity 湿度
 * @param oled OLED 对象
 */
void print_temp_humi(float temperature, float humidity, Adafruit_SSD1306 & oled);

#endif