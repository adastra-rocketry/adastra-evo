/*
  LEDs.h
*/
#pragma once

#include "Arduino.h"
#include "LEDs.h"
#include "../Settings/Settings.h"

class LEDs
{
  public:
    LEDs();
    void setRedLED(PinStatus mode);
    void setYellowLED(PinStatus mode);
    void setGreenLED(PinStatus mode);
  private:
};