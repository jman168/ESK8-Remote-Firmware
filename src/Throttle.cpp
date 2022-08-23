#include "Throttle.h"

float throttle_min, throttle_center, throttle_max;

float throttle_get_reading(int samples = 20) {
    double total = 0;
    for(int i = 0; i < samples; i++) {
        total += analogRead(THROTTLE_PIN);
        delayMicroseconds(500);
    }
    float value = total / (double)samples;
    return value;
}

void throttle_init() {    
    pinMode(THROTTLE_PIN, INPUT);
    
    throttle_center = throttle_get_reading(100);
    
    throttle_max = throttle_center;
    throttle_min = throttle_center;

    float reading = throttle_get_reading(100);
    while((throttle_max < throttle_center+20) || (throttle_min > throttle_center-20) || (abs(reading-throttle_center) > 10)) {
        reading = throttle_get_reading(100);
        throttle_min = min(throttle_min, reading);
        throttle_max = max(throttle_max, reading);
        delay(1); // keep the watchdog fed or it will reset us!
    }
}

float throttle_get_raw_throttle() {
    float value = throttle_get_reading();
    
    if(value > throttle_center) {
        return -(value-throttle_center)/(float)(throttle_max-throttle_center);
    } else {
        return (1.0-((value-throttle_min)/(float)(throttle_center-throttle_min)));
    }
}

float throttle_get_throttle() {
    float raw = throttle_get_raw_throttle();
    float value;

    if(raw > THROTTLE_DEAD_ZONE) {
        value = (raw-THROTTLE_DEAD_ZONE)/(1.0-THROTTLE_DEAD_ZONE);
    } else if(raw < -THROTTLE_DEAD_ZONE) {
        value = (raw+THROTTLE_DEAD_ZONE)/(1.0-THROTTLE_DEAD_ZONE);
    } else {
        value = 0.0;
    }

    value = value*(1.0/(1.0-THROTTLE_UPPER_LOWER_DEAD_ZONE)); // throttle upper and lower dead zone

    if(value > 1.0)
        value = 1.0;
    if(value < -1.0)
        value = -1.0;

    return value;
}

