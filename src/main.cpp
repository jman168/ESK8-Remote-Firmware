#include <Arduino.h>
#include "OLED.h"

OLED *display;

void setup() {
  Serial.begin(115200);

  display = new OLED();
}

void loop() {
  // put your main code here, to run repeatedly:
}