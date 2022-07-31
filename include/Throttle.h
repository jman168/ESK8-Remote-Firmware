#pragma once

#include <Arduino.h>

#define THROTTLE_PIN A0
#define THROTTLE_DEAD_ZONE 0.10
#define THROTTLE_UPPER_LOWER_DEAD_ZONE 0.10

/**
 * @brief Initialized the throttle potentiometer.
 * 
 */
void throttle_init();

/**
 * @brief Gets raw scaled throttle readings.
 * 
 * @return float 
 */
float throttle_get_raw_throttle();

/**
 * @brief Gets throttle with dead zones applied.
 * 
 * @return float 
 */
float throttle_get_throttle();