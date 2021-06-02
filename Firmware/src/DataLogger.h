/*
  DataLogger.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "DataPoint.h"
#include <SPI.h>

#define CSPIN 8

class DataLogger
{
  public:
    DataLogger();
    void Init();
    void Loop(SystemState &state);
  private:
    void EraseAll();
};