#pragma once
#include "SystemState.h"

class FlightStateAnalyzer {
  public:
    FlightStateAnalyzer();
    void Init();
    void Loop(SystemState &state);
  private:

};