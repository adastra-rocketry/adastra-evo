#include "LEDs.h"

LEDs::LEDs() {
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
}

void LEDs::setRedLED(PinStatus status) {
  digitalWrite(RED_LED, status);
}

void LEDs::setYellowLED(PinStatus status) {
  digitalWrite(YELLOW_LED, status);
}

void LEDs::setGreenLED(PinStatus status) {
  digitalWrite(GREEN_LED, status);
}