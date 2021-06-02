#pragma once
#include "SystemState\SystemState.h"
#include "Settings\Settings.h"
#include "Arduino.h"

class FlightStateAnalyzer {
  public:
    FlightStateAnalyzer(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
};