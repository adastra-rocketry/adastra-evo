#line 1 "E:\\AdAstra\\adastra-evo\\Firmware\\SystemState.cpp"
#include "SystemState.h"
#include "VehicleStateType.h"

SystemState::SystemState() {

}

void SystemState::Init() {
  //ErrorCode = 23;
  VehicleState = VehicleStateType::Idle;
}