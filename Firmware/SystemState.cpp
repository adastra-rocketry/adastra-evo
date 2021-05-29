#include "SystemState.h"
#include "VehicleStateType.h"

SystemState::SystemState() {

}

void SystemState::Init() {
  //ErrorCode = 23;
  VehicleState = VehicleStateType::Idle;
}

void SystemState::StartNewRecording() {
  
}