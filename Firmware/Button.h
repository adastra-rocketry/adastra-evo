/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "Settings.h"
#include "VehicleStateType.h"
#include "SystemState.h"

class Button
{
  public:
    Button();
    void Init();
    void Loop(SystemState &state);
  private:
};