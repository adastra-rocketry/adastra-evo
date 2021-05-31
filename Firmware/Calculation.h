/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "DataPoint.h"

class Calculation
{
  public:
    Calculation();
    void Init();
    void Loop(SystemState &state);
  private:
    void CalcPitchRollYaw(DataPoint &point);
};