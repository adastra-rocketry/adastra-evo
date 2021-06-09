#include "Button.h"

Button::Button(SystemState &state) : State{ state } {
  
}

void Button::Init() {
  pinMode(BUTTON_PIN, INPUT);
}

void Button::Loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    State.UpdateFlightState(VehicleStateType::LaunchIdle);
  }

}