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
    BLEService bleMainService{"181C"};
    BLECharacteristic currentDataPointServiceChar{"2AC2", BLERead | BLENotify | BLEIndicate, sizeof(DataPoint)};
    BLECharacteristic commandServiceChar{"19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, sizeof(Command)};
    long previousMillis;
    void ProcessCommand(SystemState& state);
    
    void WriteCurrentDataPoint(DataPoint &dataPoint);
};