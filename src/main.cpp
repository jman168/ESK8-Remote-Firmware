#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"
#include "Board.h"

#define BATTERY_PIN A7

OLED *display;
Throttle *throttle;

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

  display = new OLED();
  board_init();
  throttle = new Throttle(A0);
}

void loop() {
  float t = throttle->getThrottle();

  board_set_throttle(t);
  board_update();

  display->setThrottle(throttle->getThrottle());
  display->setRemoteBattery(getBattery());
  display->setBoardBattery(board_get_battery());
  display->setSpeed(board_get_speed());
  display->drawUI();
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