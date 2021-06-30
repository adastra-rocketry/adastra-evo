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
#include "RunCam.h"

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
RunCam RC{State};

unsigned long previousMillis = 0;
unsigned long previousBLEUpdateMillis = 0;
char printEvent[100];

void SensorLoop();

void setup() {
  Serial.begin(115200);
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB
  // }

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
  RC.Init();
  if(DEBUG) Serial.println("END Setup()");
}

void loop() {
  if(DEBUG) Serial.println("Begin Loop()");

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {
    State.Loop();
    Btn.Loop(); //needs to be right after State.Loop()
    Ble.Loop();
    SensorReader.Loop();    
    Calc.Loop();
    Fla.Loop();
    Tvc.Loop();
    PC.Loop();
    WD.Loop();
    SDW.Loop();
    RC.Loop();
    previousMillis = currentMillis;
  }
  if(currentMillis - previousBLEUpdateMillis >= BLE_UPDATE_INTERVAL) {
    Ble.Update();
    previousBLEUpdateMillis = currentMillis;
  }
  
  if(DEBUG) Serial.println("END Loop()");
}