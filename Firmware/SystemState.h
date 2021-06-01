/*
  SystemState.h
*/
#pragma once

#include "DataPoint.h"
#include "VehicleStateType.h"
#include "Settings.h"

class SystemState {
  public:
    SystemState();
    void Init();
    VehicleStateType VehicleState = VehicleStateType::Idle;
    DataPoint CurrentDataPoint;
    int ErrorCode;
    float HeighestAltitude = 0;
    void StartNewRecording();
    void UpdateFlightState(VehicleStateType newState);
    SettingsDto Settings;
    bool SensorReadingsReady = false;
  private:
};