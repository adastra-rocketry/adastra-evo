/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState\SystemState.h"
#include "DataPoint.h"
#include "SensorFusion.h" //SF
#include "SystemState\VehicleStateType.h"


class Calculation
{
  public:
    Calculation(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    float deltat;
    SF fusion;
    void CalcPitchRollYaw();
};