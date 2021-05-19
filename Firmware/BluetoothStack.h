#include <ArduinoBLE.h>
#include "SystemState.h"

struct Command {
  char Type;
  float Arg1;
  float Arg2;
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
    long previousMillis;
    
    void WriteCurrentDataPoint(DataPoint &dataPoint);
};