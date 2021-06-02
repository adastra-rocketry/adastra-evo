#include <ArduinoBLE.h>
#include <Arduino.h>
#include <ArduinoBLE.h>
#include "Settings\Settings.h"
#include "SystemState\VehicleStateType.h"
#include "SystemState\SystemState.h"

struct Command {
  char Type;
  float Arg1;
  float Arg2;
  char Arg3[16];
};

class BluetoothStack
{
  public:
    BluetoothStack(SystemState &state);
    void Loop();
    void Update();
    void Init();

  private:
    SystemState &State;
    BLEService bleMainService{"92aab162-79af-422f-a53b-fca7b98e2327"};
    BLECharacteristic currentDataPointServiceChar{"61e8de2f-935b-42b2-ae5b-50d444b540eb", BLERead | BLENotify | BLEIndicate, sizeof(DataPoint)};
    BLECharacteristic commandServiceChar{"da4b4a5a-bdd5-4e9f-945a-55180c8b3f53", BLERead | BLEWriteWithoutResponse | BLEWrite, sizeof(Command)};
    BLECharacteristic settingsServiceChar{"da4b4a5a-bdd5-4e9f-945a-55180c8b3b87", BLERead | BLEWriteWithoutResponse | BLEWrite, sizeof(SettingsDto)};
    BLECharacteristic pyroChannelServiceChar{"da4b4a5a-bdd5-4e9f-945a-55180c8b3f58", BLERead | BLENotify | BLEIndicate , sizeof(PyroChannelStatus)};

    void ProcessCommand(SystemState& state);
    
    void UpdateCharacteristics(SystemState &state);
};
