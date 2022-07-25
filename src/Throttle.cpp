#include "Throttle.h"

Throttle::Throttle(uint8_t pin, float min, float center, float max) {
    _pin = pin;
    _min = min;
    _center = center;
    _max = max;

    pinMode(_pin, INPUT);
}

float Throttle::getThrottle() {
    int value = analogRead(_pin);
    Serial.println(value);
    
    if(value > _center) {
        return (value-_center)/(float)(_max-_center);
    } else {
        return -(1.0-((value-_min)/(float)(_center-_min)));
    }
}