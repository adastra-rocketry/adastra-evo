#pragma once

#include "SystemState.h"

class SoundModule
{
  public:
    SoundModule();
    void Loop(SystemState &state);
  private:
    long lastTimestamp;
    void LoopError(SystemState &state);
};
