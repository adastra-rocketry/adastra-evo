#include "SystemState.h"
#include "VehicleStateType.h"
#include "Settings.h"
#include <Arduino.h>

SystemState::SystemState() {

}

void SystemState::Init() {
  //ErrorCode = 23;
  VehicleState = VehicleStateType::Idle;
}

void SystemState::StartNewRecording() {
  
}

void SystemState::UpdateFlightState(VehicleStateType newState) {
  VehicleState = newState;
  tone(BUZZER_PIN, 800, 100);
}