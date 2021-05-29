/*
  SystemState.h
*/
#pragma once

#include "DataPoint.h"
#include "VehicleStateType.h"

class SystemState {
  public:
    SystemState();
    void Init();
    VehicleStateType VehicleState = VehicleStateType::Idle;
    DataPoint CurrentDataPoint;
    int ErrorCode;
    float LaunchAltitude = 145.0f;
    float HeighestAltitude = 0;
    float PressureNN = 1027.6f;
    void StartNewRecording();
  private:
};