/*
  SystemState.h
*/
#pragma once

#include "..\DataPoint.h"
#include "VehicleStateType.h"
#include "..\Settings\Settings.h"
#include "LEDs.h"
#include "SoundModule.h"

struct PyroChannelStatus {
  bool PyroChannel1Continuity = false;
  bool PyroChannel2Continuity = false;
};

class SystemState {
  public:
    SystemState();
    void Init();
    void Loop();
    LEDs Leds;
    VehicleStateType VehicleState = VehicleStateType::Idle;
    DataPoint CurrentDataPoint;
    float HeighestAltitude = 0;
    void StartNewRecording();
    void UpdateFlightState(VehicleStateType newState);
    SettingsDto Settings;
    PyroChannelStatus PyroChannel;
    SoundModule Sound;

  private:
};