#include "FlashMemory.h"
#include "Settings/Settings.h"


FlashMemory::FlashMemory(SystemState &state) : State{ state } {

}

void FlashMemory::Init() {
  if (!SerialFlash.begin(FLASH_CS)) {
    while (1) {
      Serial.println(F("Unable to access SPI Flash chip"));
      delay(1000);
    }
  }

  unsigned char id[5];
  SerialFlash.readID(id);
  unsigned long size = SerialFlash.capacity(id);

  Serial.print(F("Flash Memory has "));
  Serial.print(size);
  Serial.println(F(" bytes."));

  ReadSettings();
}

void FlashMemory::ReadSettings() {
  if(!SerialFlash.exists("Settings")) SerialFlash.createErasable("Settings", 512);
  SerialFlashFile ff = SerialFlash.open("Settings");
  char buffer[sizeof(SettingsDto)];
  ff.read(buffer, sizeof(SettingsDto));
  memcpy(buffer, &State.Settings, sizeof(buffer));
}

void FlashMemory::WriteSettings() {
  SerialFlashFile ff = SerialFlash.open("Settings");
  ff.erase();
  SerialFlash.createErasable("Settings", 512);

  ff = SerialFlash.open("Settings");
  char buffer[sizeof(SettingsDto)];
  ff.read(buffer, sizeof(SettingsDto));
  memcpy(&State.Settings, buffer, sizeof(buffer));
  ff.write(buffer, sizeof(SettingsDto));
}

void FlashMemory::Loop() {
  
}

void FlashMemory::EraseAll() {
  
}