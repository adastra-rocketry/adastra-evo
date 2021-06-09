/*
  Watchdog.h
*/
#pragma once
#include "SystemState/SystemState.h"
#include "Arduino.h"
#include "SystemState/SystemState.h"

class Watchdog
{
  public:
    Watchdog(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
};