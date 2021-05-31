#include "SoundModule.h"
#include "SystemState.h"
#include "BluetoothStack.h"
#include "Sensors.h"
#include "Calculation.h"
#include "Arduino.h"
#include "FlightStateAnalyzer.h"
#include "Watchdog.h"
#include "SettingsStore.h"

SoundModule Sound{};
SystemState State;
SettingsStore SettingsStore;
BluetoothStack Ble;
Sensors SensorReader;
Calculation Calc;
FlightStateAnalyzer Fla;
Watchdog WD;

unsigned long previousMillis = 0;
unsigned long previousBLEUpdateMillis = 0;

void setup() {
  Serial.begin(115200);
  State.Init();
  //SettingsStore.Init(State);
  SensorReader.Init();
  Ble.Init();
  Calc.Init();
  Fla.Init();
  WD.Init();
  if(DEBUG) Serial.println("END Setup()");
}

void loop() {
  if(DEBUG) Serial.println("Begin Loop()");

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {
    Ble.Loop(State);
    SensorReader.Loop(State);
    Calc.Loop(State);
    Fla.Loop(State);
    Sound.Loop(State);
    WD.Loop(State);
    previousMillis = currentMillis;
  }
  if(currentMillis - previousBLEUpdateMillis >= BLE_UPDATE_INTERVAL) {
    Ble.Update(State);
    previousBLEUpdateMillis = currentMillis;
  }
  
  if(DEBUG) Serial.println("END Loop()");
}
