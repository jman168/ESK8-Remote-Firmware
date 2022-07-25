#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"

OLED *display;
Throttle *throttle;

void setup() {
  Serial.begin(115200);

  display = new OLED();
  throttle = new Throttle(A0, 0, 380, 760);
}

void loop() {
  display->setThrottle(throttle->getThrottle());
  display->drawUI();
}