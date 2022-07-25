#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
    public:
        OLED();

        void drawSplashScreen();

    private:
        Adafruit_SSD1306 display;
};