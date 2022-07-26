#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"

OLED *display;
Throttle *throttle;

void setup() {
  Serial.begin(115200);

  analogReference(EXTERNAL);

  display = new OLED();
  throttle = new Throttle(A0, 0, 512, 1023);
}

void loop() {
  display->setThrottle(throttle->getThrottle());
  display->drawUI();
}