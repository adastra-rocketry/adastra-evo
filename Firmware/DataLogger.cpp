#include "DataLogger.h"

DataLogger::DataLogger() {

}

void DataLogger::Init() {
  if (!SerialFlash.begin(CSPIN)) {
    while (1) {
      Serial.println(F("Unable to access SPI Flash chip"));
      delay(1000);
    }
  }

  uint8_t id[5];
  SerialFlash.readID(id);

}

void DataLogger::Loop(SystemState &state) {
  
}

void DataLogger::EraseAll() {
  SerialFlash.eraseAll();
  
  //Flash LED at 1Hz while formatting
  while (!SerialFlash.ready()) {
    delay(500);
    digitalWrite(LEDR, HIGH);
    delay(500);
    digitalWrite(LEDR, LOW);
  }

  for(uint8_t i = 0; i < 10; i++){
    delay(100);
    digitalWrite(LEDR, HIGH);
    delay(100);
    digitalWrite(LEDR, LOW);
  }
  digitalWrite(LEDR, HIGH);
}