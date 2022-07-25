#include "OLED.h"

OLED::OLED() {
    display = Adafruit_SSD1306(128, 32, &Wire);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    display.clearDisplay(); // clear the buffer
    
    drawSplashScreen(); // show splash screen
    
    delay(2500); // wait 2.5 seconds
    
    display.clearDisplay(); // clear buffer
    display.display(); // show empty buffer
}

void OLED::drawSplashScreen() {
    // draw splash screen

    // text
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(11,17);
    display.println(F("Vroom Vroom Board!"));
    display.setCursor(6,25);
    display.println(F("Im on me mums board!"));

    // board
    display.fillRect(52, 0, 64, 4, SSD1306_WHITE);
    display.fillCircle(60, 6, 4, SSD1306_WHITE);
    display.fillCircle(108, 6, 4, SSD1306_WHITE);

    // speed lines
    display.drawLine(15, 1, 45, 1, SSD1306_WHITE);
    display.drawLine(10, 4, 40, 4, SSD1306_WHITE);
    display.drawLine(15, 7, 45, 7, SSD1306_WHITE);

    // end draw splash screen
    
    display.display(); // show slash screen
}