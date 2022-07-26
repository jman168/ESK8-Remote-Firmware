#include "Throttle.h"

Throttle::Throttle(uint8_t pin, float min, float center, float max, float deadZone = 0.05) {
    _pin = pin;
    _min = min;
    _center = center;
    _max = max;
    _deadZone = deadZone;

    pinMode(_pin, INPUT);
}

float Throttle::getRawThrottle() {
    int value = analogRead(_pin);
    
    if(value > _center) {
        return (value-_center)/(float)(_max-_center);
    } else {
        return -(1.0-((value-_min)/(float)(_center-_min)));
    }
}

float Throttle::getThrottle() {
    float raw = getRawThrottle();
    if(raw > _deadZone) {
        return (raw-_deadZone)/(1.0-_deadZone);
    } else if(raw < -_deadZone) {
        return (raw+_deadZone)/(1.0-_deadZone);
    } else {
        return 0.0;
    }
}