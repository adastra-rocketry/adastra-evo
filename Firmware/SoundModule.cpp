#line 1 "E:\\AdAstra\\adastra-evo\\Firmware\\SoundModule.cpp"
#include "SoundModule.h"
#include "Settings.h"
#include "Arduino.h"
#include "SystemState.h"


SoundModule::SoundModule() {
  
}

void SoundModule::Loop(SystemState &state) {
  long now = millis();
  if(state.VehicleState == VehicleStateType::Error) {
    if(lastTimestamp < now - 500) {
      tone(BUZZER_PIN, 600, 100);
      lastTimestamp = now;
    }
  }
}
