#include <ArduinoBLE.h>
#include "SystemState.h"

struct Command {
  char Type;
  float Arg1;
  float Arg2;
  char Arg3[16];
};

class BluetoothStack
{
  public:
    BluetoothStack();
    void Loop(SystemState& state);
    void Init();

  private:
    BLEService bleMainService{"92aab162-79af-422f-a53b-fca7b98e2327"};
    BLECharacteristic currentDataPointServiceChar{"61e8de2f-935b-42b2-ae5b-50d444b540eb", BLERead | BLENotify | BLEIndicate, sizeof(DataPoint)};
    BLECharacteristic commandServiceChar{"da4b4a5a-bdd5-4e9f-945a-55180c8b3f53", BLERead | BLEWriteWithoutResponse | BLEWrite, sizeof(Command)};
    long previousMillis;
    void ProcessCommand(SystemState& state);
    
    void UpdateCharacteristics(SystemState &state);
};
