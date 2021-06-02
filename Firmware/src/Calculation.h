/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "DataPoint.h"
#include "SensorFusion.h" //SF

class Calculation
{
  public:
    Calculation();
    void Init();
    void Loop(SystemState &state);
  private:
    float deltat;
    SF fusion;
    void CalcPitchRollYaw(DataPoint &point);
};