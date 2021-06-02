/*
  Calculation.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState\SystemState.h"

class Button
{
  public:
    Button(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
};