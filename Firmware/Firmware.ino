#include "SoundModule.h"
#include "SystemState.h"
#include "BluetoothStack.h"
#include "Sensors.h"
#include "Arduino.h"
#include "FlightStateAnalyzer.h"

SoundModule Sound{};
SystemState State;
BluetoothStack Ble;
Sensors SensorReader;
FlightStateAnalyzer Fla;


void setup() {
  // put your setup code here, to run once:
  State.Init();
  SensorReader.Init();
  Ble.Init();
  Fla.Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  SensorReader.Loop(State);
  Fla.Loop(State);
  Sound.Loop(State);
  Ble.Loop(State);
}
