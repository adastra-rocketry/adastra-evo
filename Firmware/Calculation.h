/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "DataPoint.h"
#include <MahonyAHRS.h>

class Calculation
{
  public:
    Calculation();
    void Init();
    void Loop(SystemState &state);
  private:
    Mahony filter;
    void CalcPitchRollYaw(DataPoint &point);
};