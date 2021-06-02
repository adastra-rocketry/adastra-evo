#pragma once

#include "SystemState\SystemState.h"
#include "Settings\Settings.h"
#include "Arduino.h"

class SoundModule
{
  public:
    SoundModule(SystemState &state);
    void Loop();
  private:
    SystemState &State;
    long lastTimestamp;
};
