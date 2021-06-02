/*
  DataLogger.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState\SystemState.h"
#include "DataPoint.h"
#include <SPI.h>

#define CSPIN 8

class DataLogger
{
  public:
    DataLogger(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    void EraseAll();
};