#include <Arduino.h>
#include "SystemState.h"

SystemState::SystemState() {

}

void SystemState::Init() {
  VehicleState = VehicleStateType::Idle;
}

void SystemState::Loop() {
  Sound.Loop();
}

void SystemState::StartNewRecording() {
  
}

void SystemState::UpdateFlightState(VehicleStateType newState) {
  VehicleState = newState;
  tone(BUZZER_PIN, 800, 100);
}