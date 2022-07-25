#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
    public:
        OLED();

        /**
         * @brief Draws and displays the splash screen
         * 
         */
        void drawSplashScreen();

        /**
         * @brief Draws and displays the UI with all the important info
         * 
         */
        void drawUI();
        
        void setBoardBattery(float level);
        void setRemoteBattery(float level);
        void setThrottle(float level);

        /**
         * @brief Set the Speed object
         * 
         * @param speed 
         */
        void setSpeed(float speed);

    private:
        float _boardBattery = 0.0;
        float _remoteBattery = 0.0;
        float _throttle = 0.0;
        float _speed = 0.0;

        Adafruit_SSD1306 _display;
};