#pragma once

#include "..\Settings\Settings.h"
#include "Arduino.h"

class SoundModule
{
  public:
    SoundModule();
    void PlaySound(int freq, int duration);
  private:
};
