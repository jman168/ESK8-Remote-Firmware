#include "OLED.h"

OLED::OLED() {
    _display = Adafruit_SSD1306(128, 32, &Wire);
    _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    _display.clearDisplay(); // clear the buffer
    
    drawSplashScreen(); // show splash screen    
    _display.clearDisplay(); // clear buffer
}

void OLED::drawSplashScreen() {
    _display.clearDisplay(); // clear buffer

    // text
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(11,17);
    _display.println(F("Vroom Vroom Board!"));
    _display.setCursor(6,25);
    _display.println(F("Im on me mums board!"));

    // board
    _display.fillRect(52, 0, 64, 4, SSD1306_WHITE);
    _display.fillCircle(60, 7, 4, SSD1306_WHITE);
    _display.fillCircle(108, 7, 4, SSD1306_WHITE);

    // speed lines
    _display.drawLine(15, 1, 45, 1, SSD1306_WHITE);
    _display.drawLine(10, 4, 40, 4, SSD1306_WHITE);
    _display.drawLine(15, 7, 45, 7, SSD1306_WHITE);
    
    _display.display(); // show slash screen
}

void OLED::drawUI() {
    _display.clearDisplay(); // clear buffer

    // board
    _display.drawRect(52, 13, 64, 4, SSD1306_WHITE);
    _display.fillRect(53, 14, _boardBattery*64, 2, SSD1306_WHITE);
    _display.fillCircle(60, 20, 4, SSD1306_WHITE);
    _display.fillCircle(108, 20, 4, SSD1306_WHITE);

    // remote battery
    _display.drawRect(0, 0, 6, 4, SSD1306_WHITE);
    _display.drawLine(6, 1, 6, 2, SSD1306_WHITE);
    _display.fillRect(1, 1, _remoteBattery*5, 2, SSD1306_WHITE);

    // speed
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(40, 0);
    if(_speed < 9.9499999999999999999) {
        _display.print(' ');
    }
    _display.print(_speed, 1);
    _display.print(' ');
    _display.println("mph");

    // speed lines
    _display.drawLine(15, 14, 45, 14, SSD1306_WHITE);
    _display.drawLine(10, 17, 40, 17, SSD1306_WHITE);
    _display.drawLine(15, 20, 45, 20, SSD1306_WHITE);

    // throttle display
    _display.drawLine(64, 26, 64, 32, SSD1306_WHITE);
    _display.drawLine(119, 27, 119, 30, SSD1306_WHITE);
    _display.drawLine(9, 27, 9, 30, SSD1306_WHITE);
    
    if(_throttle > 0.0) {
        _display.fillRect(64, 27, _throttle*56, 4, SSD1306_WHITE);
    } if(_throttle < 0.0) {
        _display.fillRect(64+(_throttle*55), 27, (-_throttle)*55+1, 4, SSD1306_WHITE);
    }

    _display.display(); // show slash screen
}

void OLED::setBoardBattery(float level) {
    _boardBattery = level;
}

void OLED::setRemoteBattery(float level) {
    _remoteBattery = level;
}

void OLED::setThrottle(float level) {
    _throttle = level;
}

void OLED::setSpeed(float speed) {
    _speed = speed;
}