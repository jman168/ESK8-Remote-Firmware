#include "OLED.h"

float OLED_board_battery = 0.0;
float OLED_remote_battery = 0.0;
float OLED_throttle = 0.0;
float OLED_board_speed = 0.0;
bool OLED_is_connected = false;

Adafruit_SSD1306 OLED_display;

void OLED_init() {
    OLED_display = Adafruit_SSD1306(128, 32, &Wire);
    OLED_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    OLED_display.clearDisplay(); // clear the buffer
    OLED_display.display(); // display just in case
}

void OLED_draw_splash_screen() {
    OLED_display.clearDisplay(); // clear buffer

    // text
    OLED_display.setTextSize(1);
    OLED_display.setTextColor(SSD1306_WHITE);
    OLED_display.setCursor(11,17);
    OLED_display.println(F("Vroom Vroom Board!"));
    OLED_display.setCursor(6,25);
    OLED_display.println(F("Im on me mums board!"));

    // board
    OLED_display.fillRect(52, 0, 64, 4, SSD1306_WHITE);
    OLED_display.fillCircle(60, 7, 4, SSD1306_WHITE);
    OLED_display.fillCircle(108, 7, 4, SSD1306_WHITE);

    // speed lines
    OLED_display.drawLine(15, 1, 45, 1, SSD1306_WHITE);
    OLED_display.drawLine(10, 4, 40, 4, SSD1306_WHITE);
    OLED_display.drawLine(15, 7, 45, 7, SSD1306_WHITE);
    
    OLED_display.display(); // show slash screen
}

void OLED_draw_ui() {
    OLED_display.clearDisplay(); // clear buffer

    // remote battery
    OLED_display.drawRect(0, 0, 6, 4, SSD1306_WHITE);
    OLED_display.drawLine(6, 1, 6, 2, SSD1306_WHITE);
    OLED_display.fillRect(1, 1, OLED_remote_battery*5, 2, SSD1306_WHITE);

    if(OLED_is_connected || (millis()/500)%2==0) {
        // board
        OLED_display.drawRect(52, 13, 64, 4, SSD1306_WHITE);
        OLED_display.fillRect(53, 14, OLED_board_battery*64, 2, SSD1306_WHITE);
        OLED_display.fillCircle(60, 20, 4, SSD1306_WHITE);
        OLED_display.fillCircle(108, 20, 4, SSD1306_WHITE);
    
        // speed
        OLED_display.setTextSize(1);
        OLED_display.setTextColor(SSD1306_WHITE);
        OLED_display.setCursor(40, 0);
        if(OLED_board_speed < 9.9499999999999999999) {
            OLED_display.print(' ');
        }
        OLED_display.print(OLED_board_speed, 1);
        OLED_display.print(' ');
        OLED_display.println("mph");

        // speed lines
        OLED_display.drawLine(15, 14, 45, 14, SSD1306_WHITE);
        OLED_display.drawLine(10, 17, 40, 17, SSD1306_WHITE);
        OLED_display.drawLine(15, 20, 45, 20, SSD1306_WHITE);
    }

    // throttle display
    OLED_display.drawLine(64, 26, 64, 32, SSD1306_WHITE);
    OLED_display.drawLine(119, 27, 119, 30, SSD1306_WHITE);
    OLED_display.drawLine(9, 27, 9, 30, SSD1306_WHITE);
    
    if(OLED_throttle > 0.0) {
        OLED_display.fillRect(64, 27, OLED_throttle*56, 4, SSD1306_WHITE);
    } if(OLED_throttle < 0.0) {
        OLED_display.fillRect(64+(OLED_throttle*55), 27, (-OLED_throttle)*55+1, 4, SSD1306_WHITE);
    }

    OLED_display.display(); // display buffer
}

void OLED_set_board_battery(float level) {
    OLED_board_battery = level;
}

void OLED_set_remote_battery(float level) {
    OLED_remote_battery = level;
}

void OLED_set_throttle(float throttle) {
    OLED_throttle = throttle;
}

void OLED_set_board_speed(float speed) {
    OLED_board_speed = speed;
}

void OLED_set_is_connected(bool connected) {
    OLED_is_connected = connected;
}