#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"
#include "Board.h"

float z = 0.0;

void setup() {
  Serial.begin(115200);

  while(!Serial);

  OLED_init();
  OLED_draw_splash_screen();
  board_init();
  throttle_init();
}

void loop() {
  float t = throttle_get_throttle();

  board_set_throttle(t);
  board_update();

  OLED_set_throttle(t);
  OLED_set_remote_battery(0.0);
  OLED_set_board_battery(board_get_battery());
  OLED_set_board_speed(board_get_speed());
  OLED_set_motor_temperature(board_get_motor_temperature());
  OLED_set_is_connected(board_is_connected());
  OLED_draw_ui();
}