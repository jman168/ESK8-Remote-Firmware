#include <Arduino.h>
#include "OLED.h"
#include "Throttle.h"

#define BATTERY_PIN A7

OLED *display;
Throttle *throttle;

float getBattery();

void setup() {
  Serial.begin(115200);

  analogReference(EXTERNAL);

  pinMode(BATTERY_PIN, INPUT);


  display = new OLED();
  throttle = new Throttle(A0, 0, 512, 1023);
}

void loop() {
  display->setThrottle(throttle->getThrottle());
  display->setRemoteBattery(getBattery());
  display->drawUI();
}

float getBattery() {
  int value = analogRead(BATTERY_PIN);
  float voltage = (value/1023.0)*3.3*2.0;

  if(voltage < 3.3)
    return 0.0;

  return (voltage-3.3)/(4.2-3.3);
}