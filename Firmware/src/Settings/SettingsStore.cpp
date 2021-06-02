#include "SettingsStore.h"


SettingsStore::SettingsStore(SystemState &state) : State{ state } {

}

void SettingsStore::Init() {
  ReadFromEEPROM(State.Settings);
}

void SettingsStore::ReadFromEEPROM(SettingsDto &settings) {
  uint8_t data[sizeof(settings)];
  NVRAM.read_block(data, 0, sizeof(settings));
  memcpy(data, &settings, sizeof(settings));
}

void SettingsStore::WriteToEEPROM(SettingsDto &settings) {
  uint8_t data[sizeof(SettingsDto)];
  memcpy(&settings, data, sizeof(SettingsDto));
  NVRAM.write_block(data, 0, sizeof(data));
}