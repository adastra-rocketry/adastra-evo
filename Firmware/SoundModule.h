#pragma once

#include "SystemState.h"

const int DURATION_BEEP = 200;
const int DURATION_PAUSE = 200;


class SoundModule
{
  public:
    SoundModule();
    void Loop(SystemState &state);
  private:
    long lastTimestamp;
    void LoopError(SystemState &state);
};
