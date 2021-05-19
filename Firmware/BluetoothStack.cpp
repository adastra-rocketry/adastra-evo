#line 1 "E:\\AdAstra\\adastra-evo\\Firmware\\BluetoothStack.cpp"
#include "Arduino.h"
#include <ArduinoBLE.h>
#include "BluetoothStack.h"
#include "Settings.h"

BluetoothStack::BluetoothStack() {
  
}

void BluetoothStack::Init() {  
  // begin initialization
  if (!BLE.begin()) {
    if(DEBUG) Serial.println("starting BLE failed!");
    while (1);
  }

    /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  BLE.setLocalName("AdAstra Evo");
  BLE.setAdvertisedService(bleMainService); // add the service UUID
  bleMainService.addCharacteristic(currentDataPointServiceChar);
  
  BLE.addService(bleMainService);

  
  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();
  if(DEBUG) Serial.println("Bluetooth device active, waiting for connections...");
}

void BluetoothStack::Loop(SystemState &state) {  
  BLE.advertise();  //this is the arduino libs static stuff
  WriteCurrentDataPoint(state.CurrentDataPoint);
}


void BluetoothStack::WriteCurrentDataPoint(DataPoint& dataPoint) {
    long currentMillis = millis();
    // if 200ms have passed
    if(currentMillis - previousMillis >= BLE_UPDATE_INTERVAL) {
      unsigned char b[sizeof(dataPoint)];
      memcpy(b, &dataPoint, sizeof(dataPoint));
      currentDataPointServiceChar.writeValue(b, sizeof(b)); // and publish it via BT
      previousMillis = currentMillis;
    }
}
