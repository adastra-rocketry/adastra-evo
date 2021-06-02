#include "SoundModule.h"

SoundModule::SoundModule(SystemState &state) : State{ state } {
  tone(BUZZER_PIN, 800, 100);
}

void SoundModule::Loop() {
  long now = millis();
  if(State.VehicleState == VehicleStateType::Error) {
    if(lastTimestamp < now - 500) {
      tone(BUZZER_PIN, 600, 100);
      lastTimestamp = now;
    }
  }
}
