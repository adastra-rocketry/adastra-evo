#pragma once

#include <NVRAM.h>
#include "Settings.h"
#include "SystemState.h"


class SettingsStore
{
  public:
    SettingsStore();
    void Init(SystemState &state);
  private:
    void ReadFromEEPROM(SettingsDto &settings);
    void WriteToEEPROM(SettingsDto &settings);
};
