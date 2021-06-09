/*
  RunCam.h
*/
#pragma once
#include "SystemState\SystemState.h"
#include "Arduino.h"
#include "SystemState\SystemState.h"

class RunCam
{
  public:
    RunCam(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
};