#pragma once 

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

/**
 * @brief Initializes radio communication with the board.
 * 
 */
void board_init();

/**
 * @brief Sends throttle data, checks buffer for data from the board, etc... 
 * 
 */
void board_update();

/**
 * @brief Sets the board throttle.
 * 
 * @param throttle 
 */
void board_set_throttle(float throttle);

/**
 * @brief Gets the speed of the board in miles per hour.
 * 
 * @return float 
 */
float board_get_speed();

/**
 * @brief Gets the battery level of the board as a number from 0.0 to 1.0
 * 
 * @return float 
 */
float board_get_battery();

/**
 * @brief Gets if two way communication is established with the board.
 * 
 * @return true 
 * @return false 
 */
bool board_is_connected();