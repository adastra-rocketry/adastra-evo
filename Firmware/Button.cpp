#include "Button.h"

Button::Button() {
  
}

void Button::Init() {
  pinMode(BUTTON_PIN, INPUT);
}

void Button::Loop(SystemState &state) {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    state.UpdateFlightState(VehicleStateType::Calibrating);
  }

}