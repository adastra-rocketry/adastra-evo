#pragma once

#include <NVRAM.h>
#include "Settings.h"
#include "..\SystemState\SystemState.h"

class SettingsStore
{
  public:
    SettingsStore(SystemState &state);
    void Init();
  private:
    SystemState &State;
    void ReadFromEEPROM(SettingsDto &settings);
    void WriteToEEPROM(SettingsDto &settings);
};
