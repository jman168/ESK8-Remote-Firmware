#pragma once

#include <Arduino.h>

class Throttle {
    public: 
        Throttle(uint8_t pin, float min, float center, float max, float deadZone = 0.05);

        float getRawThrottle();
        float getThrottle();

    private:
        float _min, _center, _max, _deadZone;
        uint8_t _pin;
};