#include "SoundModule.h"

SoundModule::SoundModule() {
  tone(BUZZER_PIN, 800, 100);
}

void SoundModule::PlaySound(int freq, int duration) {
  tone(BUZZER_PIN, freq, duration);
}