#include "SettingsStore.h"
#include "Settings.h"
#include "SystemState.h"

SettingsStore::SettingsStore() {

}

void SettingsStore::Init(SystemState &state) {
  ReadFromEEPROM(state.Settings);
}

void SettingsStore::ReadFromEEPROM(SettingsDto &settings) {
  uint8_t data[sizeof(SettingsDto)];
  NVRAM.read_block(data, 0, sizeof(settings));
  memcpy(data, &settings, sizeof(settings));
}

void SettingsStore::WriteToEEPROM(SettingsDto &settings) {
  uint8_t data[sizeof(SettingsDto)];
  memcpy(&settings, data, sizeof(SettingsDto));
  NVRAM.write_block(data, 0, sizeof(data));
}