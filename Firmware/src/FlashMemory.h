/*
  FlashMemory.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState\SystemState.h"
#include "DataPoint.h"
#include <SPI.h>
#include <SerialFlash.h>

#define FLASH_CS 8

class FlashMemory
{
  public:
    FlashMemory(SystemState &state);
    void Init();
    void Loop();
    void WriteSettings();
  private:
    SystemState &State;
    void EraseAll();
    void ReadSettings();
};