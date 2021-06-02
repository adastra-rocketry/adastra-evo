#include "LEDs.h"

LEDs::LEDs() {
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
}

void LEDs::setRedLED(PinMode mode) {
  digitalWrite(RED_LED, mode);
}

void LEDs::setYellowLED(PinMode mode) {
  digitalWrite(YELLOW_LED, mode);
}

void LEDs::setGreenLED(PinMode mode) {
  digitalWrite(GREEN_LED, mode);
}