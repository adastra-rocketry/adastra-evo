#include "SoundModule.h"
#include "SystemState.h"
#include "BluetoothStack.h"
#include "Sensors.h"
#include "Calculation.h"
#include "Arduino.h"
#include "FlightStateAnalyzer.h"
#include "Watchdog.h"
#include "DataLogger.h"
#include "SettingsStore.h"

#include <mbed.h>
#include <mbed_mem_trace.h>

SoundModule Sound{};
SystemState State;
SettingsStore SettingsStore;
BluetoothStack Ble;
Sensors SensorReader;
Calculation Calc;
FlightStateAnalyzer Fla;
DataLogger DL;
Watchdog WD;

unsigned long previousMillis = 0;
unsigned long previousBLEUpdateMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire1.begin();
  InitLEDs();
  State.Init();
  //SettingsStore.Init(State);
  SensorReader.Init();
  DL.Init();
  Ble.Init();
  Calc.Init();
  Fla.Init();
  WD.Init();
  if(DEBUG) Serial.println("END Setup()");
}

char printEvent[100];

void loop() {
  if(DEBUG) Serial.println("Begin Loop()");

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {
    Ble.Loop(State);
    SensorReader.Loop(State);    
    Calc.Loop(State);
    Fla.Loop(State);
    Sound.Loop(State);
    DL.Loop(State);
    WD.Loop(State);
    previousMillis = currentMillis;
  }
  if(currentMillis - previousBLEUpdateMillis >= BLE_UPDATE_INTERVAL) {
    Ble.Update(State);
    previousBLEUpdateMillis = currentMillis;
    //print_memory_info(printEvent, sizeof(printEvent));
  }
  
  if(DEBUG) Serial.println("END Loop()");
}

void InitLEDs() {
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
}

void print_memory_info(char* printEvent, int iSize) {
    // allocate enough room for every thread's stack statistics
    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
 
    cnt = mbed_stats_stack_get_each(stats, cnt);
    for (int i = 0; i < cnt; i++) {
        snprintf_P(printEvent, iSize, "Thread: 0x%lX, Stack size: %lu / %lu\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
        Serial.println(printEvent);
    }
    free(stats);
 
    // Grab the heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    snprintf_P(printEvent, iSize, "Heap size: %lu / %lu bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
    Serial.println(printEvent);
}