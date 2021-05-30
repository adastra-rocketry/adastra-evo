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


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  SensorReader.Loop(State);
  Calc.Loop(State);
  Fla.Loop(State);
  Sound.Loop(State);
  Ble.Loop(State);
  WD.Loop(State);
  if(DEBUG) Serial.println("END Loop()");
}
