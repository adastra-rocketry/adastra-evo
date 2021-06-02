#include "Watchdog.h"

Watchdog::Watchdog(SystemState &state) : State{ state } {
  
}

void Watchdog::Init() {
  #if defined(ARDUINO_ARDUINO_NANO33BLE)
    // This segment of code only exists when compiled and loaded onto an
    // Arduino Nano 33 BLE and BLE Sense

    //Configure WDT.
    NRF_WDT->CONFIG         = 0x01;             // Configure WDT to run when CPU is asleep
    NRF_WDT->CRV            = 40 * 32768;        // Set timeout for 2 seconds
    NRF_WDT->RREN           = 0x01;             // Enable the RR[0] reload register
    NRF_WDT->TASKS_START    = 1;                // Start WDT
  #endif
}

void Watchdog::Loop() {
  #if defined(ARDUINO_ARDUINO_NANO33BLE)
    // This segment of code only exists when compiled and loaded onto an
    // Arduino Nano 33 BLE and BLE Sense
    if(DEBUG) Serial.println("Rearming WD");
    NRF_WDT->RR[0] = WDT_RR_RR_Reload;
  #endif
}