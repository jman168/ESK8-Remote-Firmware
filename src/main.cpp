#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"
#include "Board.h"

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
  OLED_draw_ui();
}