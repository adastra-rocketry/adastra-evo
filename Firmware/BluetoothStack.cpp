#include "Arduino.h"
#include <ArduinoBLE.h>
#include "BluetoothStack.h"
#include "Settings.h"
#include "VehicleStateType.h"

#define RSSI_REASONABLE_SIGNAL -80 // A reasonable RSSI signal strength

void blePeripheralConnectHandler(BLEDevice central) {
  Serial.println("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  Serial.println("Disconnected event, central: ");
  Serial.println(central.address());
}


BluetoothStack::BluetoothStack() {
  
}

void BluetoothStack::Init() {  
  if(DEBUG) Serial.println("BEGIN BluetoothStack::Init()");
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
  bleMainService.addCharacteristic(commandServiceChar);
  bleMainService.addCharacteristic(settingsServiceChar);
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  BLE.addService(bleMainService);
  BLE.setConnectable(true);

  
  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();
  if(DEBUG) Serial.println("Bluetooth device active, waiting for connections...");
  if(DEBUG) Serial.println("END BluetoothStack::Init()");
}



void BluetoothStack::Loop(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::Loop()");
  BLE.poll();
  BLE.advertise();
  BLEDevice central = BLE.central();
  if (central) {
    if (central.connected()) {
      // Check for reasonable RSSI signal strength.
      if (central.rssi() >= RSSI_REASONABLE_SIGNAL) {
        UpdateCharacteristics(state);  


        ProcessCommand(state);
      } else {
        // Until the defect is fixed, we force disconnection
        // of the central device.
        if (!central.disconnect()) {
          central.disconnect();          
        }                
      }

    }
  }
  if(DEBUG) Serial.println("END BluetoothStack::Loop()");
}


void BluetoothStack::UpdateCharacteristics(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::UpdateCharacteristics()");
  long currentMillis = millis();
  // if 200ms have passed
  if(currentMillis - previousMillis >= BLE_UPDATE_INTERVAL) {
    if(DEBUG) Serial.println("Update currentDataPointServiceChar");
    unsigned char b[sizeof(state.CurrentDataPoint)];
    memcpy(b, &state.CurrentDataPoint, sizeof(state.CurrentDataPoint));
    currentDataPointServiceChar.writeValue(b, sizeof(b)); // and publish it via BT


    unsigned char bs[sizeof(state.Settings)];
    memcpy(bs, &state.Settings, sizeof(state.Settings));
    settingsServiceChar.writeValue(bs, sizeof(bs)); // and publish it via BT
    
    previousMillis = currentMillis;
  }
  if(DEBUG) Serial.println("END BluetoothStack::UpdateCharacteristics()");
}

void BluetoothStack::ProcessCommand(SystemState& state) {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::ProcessCommand()");
  if (commandServiceChar.written()) {
    Command command;
    const uint8_t* b;
    b = commandServiceChar.value();
    memcpy(&command, b, sizeof(command));
    
    if(DEBUG) {
      Serial.print("Got new command:");
      Serial.print(command.Type);
      Serial.println();
      Serial.print(command.Arg1, 3);
      Serial.println();
      Serial.print(command.Arg2, 3);
      Serial.println();
    }

    switch(command.Type) {
      case 'r':
        state.StartNewRecording();
        break;
      case 'l':
        state.VehicleState = VehicleStateType::LaunchIdle;
        break;
      case 's':
        state.Settings.LaunchAltitude = command.Arg1;
        state.Settings.PressureNN = command.Arg2;
        strcpy(state.Settings.Name, command.Arg3);
        state.StartNewRecording();
        break;
      default:
        if(DEBUG) {
          Serial.print("Unknown command: ");
          Serial.println(command.Type);
        }
    }
  }
  if(DEBUG) Serial.println("END BluetoothStack::ProcessCommand()");
}
