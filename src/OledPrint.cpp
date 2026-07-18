#include "OledPrint.hpp"
#include "Fonts.hpp"

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void display_num_let(byte row, byte col, const unsigned char font[16], Adafruit_SSD1306 & oled)
{
    if (col < 0 || col > 15 || row < 0 || row > 3)
    {
        Serial.println("坐标超出屏幕显示范围");
        return;
    }

    byte x = col * 8;
    byte y = row * 16;
    
    oled.drawBitmap(x, y, font, NUMBER_LETTER_FONT_WIDTH, NUMBER_LETTER_FONT_HEIGHT, SSD1306_WHITE);
}

void display_chinese(byte row, byte col, const unsigned char font[32], Adafruit_SSD1306 & oled)
{
    if (col < 0 || col > 7 || row < 0 || row > 3)
    {
        Serial.println("坐标超出屏幕显示范围");
        return; 
    }

    byte x = col * 16;
    byte y = row * 16;

    oled.drawBitmap(x, y, font, CHINESE_FONT_WIDTH, CHINESE_FONT_HEIGHT, SSD1306_WHITE);
}

void print_week(byte week, Adafruit_SSD1306 & oled)
{
    display_chinese(1, 2, chinese_fonts[7], oled);
    display_chinese(1, 3, chinese_fonts[8], oled);
    display_chinese(1, 4, chinese_fonts[week], oled);
}

void print_init_info(byte step, Adafruit_SSD1306 & oled)
{
    if (step < 1 )
    {
        Serial.println("步骤序号错误！");
        return;
    }

    oled.clearDisplay();

    if (1 == step) // 正在连接WiFi
    {
        display_chinese(0, 1, chinese_fonts[9], oled);
        display_chinese(0, 2, chinese_fonts[10], oled);
        display_chinese(0, 3, chinese_fonts[11], oled);
        display_chinese(0, 4, chinese_fonts[12], oled);
        display_num_let(0, 10, letter_fonts[0], oled);
        display_num_let(0, 11, letter_fonts[2], oled);
        display_num_let(0, 12, letter_fonts[1], oled);
        display_num_let(0, 13, letter_fonts[2], oled);
    }
    else if (2 == step) // 连接WiFi成功
    {
        display_chinese(0, 1, chinese_fonts[11], oled);
        display_chinese(0, 2, chinese_fonts[12], oled);
        display_num_let(0, 6, letter_fonts[0], oled);
        display_num_let(0, 7, letter_fonts[2], oled);
        display_num_let(0, 8, letter_fonts[1], oled);
        display_num_let(0, 9, letter_fonts[2], oled);
        display_chinese(0, 5, chinese_fonts[13], oled);
        display_chinese(0, 6, chinese_fonts[14], oled);
    }
    else if (3 == step) // 正在同步时间
    {
        display_chinese(0, 1, chinese_fonts[9], oled);
        display_chinese(0, 2, chinese_fonts[10], oled); 
        display_chinese(0, 3, chinese_fonts[15], oled);
        display_chinese(0, 4, chinese_fonts[16], oled);
        display_chinese(0, 5, chinese_fonts[17], oled);
        display_chinese(0, 6, chinese_fonts[18], oled);
    }

    else if (4 == step) // 同步时间成功
    {
        display_chinese(0, 1, chinese_fonts[15], oled);
        display_chinese(0, 2, chinese_fonts[16], oled);
        display_chinese(0, 3, chinese_fonts[17], oled);
        display_chinese(0, 4, chinese_fonts[18], oled);
        display_chinese(0, 5, chinese_fonts[13], oled);
        display_chinese(0, 6, chinese_fonts[14], oled);
    }

    oled.display();
}

void print_date(int year, byte mon, byte day, Adafruit_SSD1306 & oled)
{
    display_num_let(0, 3, number_fonts[year / 1000], oled);
    display_num_let(0, 4, number_fonts[(year % 1000) / 100], oled);
    display_num_let(0, 5, number_fonts[(year % 100) / 10], oled);
    display_num_let(0, 6, number_fonts[year % 10], oled);
    display_num_let(0, 7, letter_fonts[4], oled);
    display_num_let(0, 8, number_fonts[mon / 10], oled);
    display_num_let(0, 9, number_fonts[mon % 10], oled);
    display_num_let(0, 10, letter_fonts[4], oled);
    display_num_let(0, 11, number_fonts[day / 10], oled);
    display_num_let(0, 12, number_fonts[day % 10], oled);
}

void print_time(byte hour, byte min, byte sec, Adafruit_SSD1306 & oled)
{
    display_num_let(2, 3, number_fonts[hour / 10], oled);
    display_num_let(2, 4, number_fonts[hour % 10], oled);
    display_num_let(2, 5, letter_fonts[3], oled);
    display_num_let(2, 6, number_fonts[min / 10], oled);
    display_num_let(2, 7, number_fonts[min % 10], oled);
    display_num_let(2, 8, letter_fonts[3], oled);
    display_num_let(2, 9, number_fonts[sec / 10], oled);
    display_num_let(2, 10, number_fonts[sec % 10], oled);
}

void print_temp_humi(float temperature, float humidity, Adafruit_SSD1306 & oled)
{
    if (temperature < 0)
    {
        display_num_let(3, 0, letter_fonts[6], oled);
    }

    display_num_let(3, 1, number_fonts[(int)temperature / 10], oled);
    display_num_let(3, 2, number_fonts[(int)temperature % 10], oled);
    display_num_let(3, 3, letter_fonts[4], oled);
    display_num_let(3, 4, number_fonts[(int)(temperature * 10) % 10], oled);
    display_num_let(3, 5, number_fonts[(int)(temperature * 100) % 10], oled);
    display_chinese(3, 3, chinese_fonts[19], oled);

    display_num_let(3, 9, number_fonts[(int)humidity / 10], oled);
    display_num_let(3, 10, number_fonts[(int)humidity % 10], oled);
    display_num_let(3, 11, letter_fonts[4], oled);
    display_num_let(3, 12, number_fonts[(int)(humidity * 10) % 10], oled);
    display_num_let(3, 13, number_fonts[(int)(humidity * 100) % 10], oled);
    display_num_let(3, 14, letter_fonts[5], oled);
}