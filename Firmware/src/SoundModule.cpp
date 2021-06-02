#include "SoundModule.h"
#include "Settings.h"
#include "Arduino.h"
#include "SystemState.h"


SoundModule::SoundModule() {
  tone(BUZZER_PIN, 800, 100);
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
