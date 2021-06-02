#pragma once

#include "Settings\Settings.h"

#include "Arduino.h"
#include "SystemState\SystemState.h"

class PyroChannels
{
  public:
    PyroChannels(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    void CheckContinuity();
};