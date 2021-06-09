#include "SystemState/SystemState.h"
#include "BluetoothStack.h"
#include "Sensors.h"
#include "Calculation.h"
#include "Arduino.h"
#include "FlightStateAnalyzer.h"
#include "Watchdog.h"
#include "Button.h"
#include "PyroChannels.h"
#include "TVC.h"
#include "SDWriter.h"

SystemState State;
Sensors SensorReader{State};
Calculation Calc{State};
FlightStateAnalyzer Fla{State};
BluetoothStack Ble{State};
Watchdog WD{State};
Button Btn{State};
PyroChannels PC{State};
TVC Tvc{State};
SDWriter SDW{State};

unsigned long previousMillis = 0;
unsigned long previousBLEUpdateMillis = 0;
char printEvent[100];

void SensorLoop();

void setup() {
  Serial.begin(115200);
  State.Init();
  Btn.Init();
  SensorReader.Init();
  Ble.Init();
  Calc.Init();
  Fla.Init();
  WD.Init();
  PC.Init();
  Tvc.Init();
  SDW.Init();
  if(DEBUG) Serial.println("END Setup()");
}

void loop() {
  if(DEBUG) Serial.println("Begin Loop()");

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {
    State.Loop();
    Ble.Loop();
    SensorReader.Loop();    
    Calc.Loop();
    Btn.Loop();
    Fla.Loop();
    Tvc.Loop();
    PC.Loop();
    WD.Loop();
    SDW.Loop();
    previousMillis = currentMillis;
  }
  if(currentMillis - previousBLEUpdateMillis >= BLE_UPDATE_INTERVAL) {
    Ble.Update();
    previousBLEUpdateMillis = currentMillis;
  }
  
  if(DEBUG) Serial.println("END Loop()");
}