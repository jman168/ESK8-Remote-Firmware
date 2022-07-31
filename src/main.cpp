#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"
#include "Board.h"

#define BATTERY_PIN A7

FILE f_out;
int sput(char c, __attribute__((unused)) FILE* f) {return !Serial.write(c);}

float getBattery();

void setup() {
  Serial.begin(115200);
  
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE); // cf https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaf41f158c022cbb6203ccd87d27301226
  stdout = &f_out;

  while(!Serial);

  analogReference(EXTERNAL);

  pinMode(BATTERY_PIN, INPUT);

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
  OLED_set_remote_battery(getBattery());
  OLED_set_board_battery(board_get_battery());
  OLED_set_board_speed(board_get_speed());
  OLED_draw_ui();
}

float getBattery() {
  float total = 0;
  for(int i = 0; i < 10; i++) {
    total += analogRead(BATTERY_PIN);
  }
  float value = total / 10.0;
  
  float voltage = (value/1023.0)*3.43*2.0;

  if(voltage < 3.0)
    return 0.0;

  return (voltage-3.0)/(4.2-3.0);
}