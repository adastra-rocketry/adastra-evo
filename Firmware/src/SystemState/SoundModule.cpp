#include "SoundModule.h"

SoundModule::SoundModule() {
  //pinMode(BUZZER_PIN, OUTPUT);
  PlaySound(1, 1);
}

void SoundModule::PlaySound(int freq, int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
}

void SoundModule::Loop() {
}