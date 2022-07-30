#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * @brief Initializes the OLED screen.
 * 
 */
void OLED_init();

/**
 * @brief Draws the custom splash screen to the OLED.
 * 
 */
void OLED_draw_splash_screen();

/**
 * @brief Draws one frame of the UI according to current data.
 * 
 */
void OLED_draw_ui();

/**
 * @brief Sets the boards battery level from 0.0 to 1.0
 * 
 * @param level 
 */
void OLED_set_board_battery(float level);

/**
 * @brief Sets the boards speed in miles per hour.
 * 
 * @param speed 
 */
void OLED_set_board_speed(float speed);

/**
 * @brief Sets the remotes battery level from 0.0 to 1.0
 * 
 * @param level 
 */
void OLED_set_remote_battery(float level);

/**
 * @brief Sets the throttle input from -1.0 to 1.0
 * 
 * @param throttle 
 */
void OLED_set_throttle(float throttle);