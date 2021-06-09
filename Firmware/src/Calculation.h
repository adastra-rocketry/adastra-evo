/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState\SystemState.h"
#include "DataPoint.h"
#include "SensorFusion.h" //SF
#include "SystemState\VehicleStateType.h"
#include <SimpleKalmanFilter.h>


class Calculation
{
  public:
    Calculation(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    SimpleKalmanFilter PressureKalmanFilter{2, 2, 0.01};
    float deltat;
    SF fusion;
    void CalcPitchRollYaw();
    void UpdateKalmanFilters();
};