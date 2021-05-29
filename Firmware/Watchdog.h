/*
  Watchdog.h
*/
#pragma once

#include "SystemState.h"

class Watchdog
{
  public:
    Watchdog();
    void Init();
    void Loop(SystemState &state);
  private:
};