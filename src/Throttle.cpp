#include "Throttle.h"

Throttle::Throttle(uint8_t pin, float deadZone = 0.05) {
    _pin = pin;
    
    pinMode(_pin, INPUT);
    
    _center = getReading();
    
    _max = _center;
    _min = _center;

    float reading = getReading();
    while((_max < _center+20) || (_min > _center-20) || (abs(reading-_center) > 10)) {
        reading = getReading();
        _min = min(_min, reading);
        _max = max(_max, reading);
    }

    _deadZone = deadZone;
}

float Throttle::getRawThrottle() {
    float value = getReading();
    
    if(value > _center) {
        return -(value-_center)/(float)(_max-_center);
    } else {
        return (1.0-((value-_min)/(float)(_center-_min)));
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

float Throttle::getReading() {
    float total = 0;
    for(int i = 0; i < 10; i++) {
        total += analogRead(_pin);
    }
    float value = total / 10.0;
    return value;
}