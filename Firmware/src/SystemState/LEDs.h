/*
  LEDs.h
*/
#pragma once

#include "Arduino.h"
#include "LEDs.h"
#include "..\Settings\Settings.h"

class LEDs
{
  public:
    LEDs();
    void setRedLED(PinMode mode);
    void setYellowLED(PinMode mode);
    void setGreenLED(PinMode mode);
  private:
};