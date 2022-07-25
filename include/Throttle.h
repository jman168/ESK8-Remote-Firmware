#pragma once

#include <Arduino.h>

class Throttle {
    public: 
        Throttle(uint8_t pin, float min, float center, float max);

        float getThrottle();

    private:
        float _min, _center, _max;
        uint8_t _pin;
};