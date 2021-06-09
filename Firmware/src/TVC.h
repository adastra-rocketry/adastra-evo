/*
  Watchdog.h
*/
#pragma once
#include "SystemState\SystemState.h"
#include "Arduino.h"
#include "SystemState\SystemState.h"
#include <Servo.h>

class TVC
{
  public:
    TVC(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    Servo ServoX; // Define our Servo
    Servo ServoY; // Define our Servo
};