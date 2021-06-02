#include "BluetoothStack.h"

BluetoothStack::BluetoothStack(SystemState &state) : State{ state } {
  
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
  bleMainService.addCharacteristic(pyroChannelServiceChar);
  BLE.addService(bleMainService);
  
  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();
  if(DEBUG) Serial.println("Bluetooth device active, waiting for connections...");
  if(DEBUG) Serial.println("END BluetoothStack::Init()");
}

void BluetoothStack::Loop() {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::Loop()");
  BLE.poll();
  BLE.advertise();
  if(DEBUG) Serial.println("END BluetoothStack::Loop()");
}

void BluetoothStack::Update() {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::Update()");
  
  State.Leds.setYellowLED(HIGH);
  BLEDevice central = BLE.central();
  if (central) {
    if (central.connected()) {
      UpdateCharacteristics(State);
      ProcessCommand(State);
    }
  }
  State.Leds.setYellowLED(LOW);
  if(DEBUG) Serial.println("END BluetoothStack::Update()");
}

void BluetoothStack::UpdateCharacteristics(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN BluetoothStack::UpdateCharacteristics()");
  unsigned char bDP[sizeof(State.CurrentDataPoint)];
  memcpy(bDP, &State.CurrentDataPoint, sizeof(State.CurrentDataPoint));
  currentDataPointServiceChar.writeValue(bDP, sizeof(bDP)); // and publish it via BT

  unsigned char bPC[sizeof(State.PyroChannel)];
  memcpy(bPC, &State.PyroChannel, sizeof(State.PyroChannel));
  pyroChannelServiceChar.writeValue(bPC, sizeof(bPC)); // and publish it via BT
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
        State.StartNewRecording();
        break;
      case 'l':
        State.UpdateFlightState(VehicleStateType::LaunchIdle);
        break;
      case 's':
        State.Settings.LaunchAltitude = command.Arg1;
        State.Settings.PressureNN = command.Arg2;
        strcpy(State.Settings.Name, command.Arg3);
        State.StartNewRecording();
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
