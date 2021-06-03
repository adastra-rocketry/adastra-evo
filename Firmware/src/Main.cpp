#include "SystemState\SystemState.h"
#include "BluetoothStack.h"
#include "Sensors.h"
#include "Calculation.h"
#include "Arduino.h"
#include "FlightStateAnalyzer.h"
#include "Watchdog.h"
#include "FlashMemory.h"
#include "Button.h"
#include "PyroChannels.h"

#include <mbed.h>
#include <mbed_mem_trace.h>

SystemState State;
BluetoothStack Ble{State};
Sensors SensorReader{State};
Calculation Calc{State};
FlightStateAnalyzer Fla{State};
FlashMemory FL{State};
Watchdog WD{State};
Button Btn{State};
PyroChannels PC{State};

unsigned long previousMillis = 0;
unsigned long previousBLEUpdateMillis = 0;
char printEvent[100];

void SensorLoop();

void setup() {
  Serial.begin(115200);
  State.Init();
  Btn.Init();
  SensorReader.Init();
  FL.Init();
  Ble.Init();
  Calc.Init();
  Fla.Init();
  WD.Init();
  PC.Init();
  if(DEBUG) Serial.println("END Setup()");
}



void loop() {
  if(DEBUG) Serial.println("Begin Loop()");

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {
    Ble.Loop();
    SensorReader.Loop();    
    Calc.Loop();
    Btn.Loop();
    Fla.Loop();
    PC.Loop();
    FL.Loop();
    WD.Loop();
    previousMillis = currentMillis;
  }
  if(currentMillis - previousBLEUpdateMillis >= BLE_UPDATE_INTERVAL) {
    Ble.Update();
    previousBLEUpdateMillis = currentMillis;
    //print_memory_info(printEvent, sizeof(printEvent));
  }
  
  if(DEBUG) Serial.println("END Loop()");
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