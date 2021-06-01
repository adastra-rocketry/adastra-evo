#include "Calculation.h"
#include "SystemState.h"
#include "DataPoint.h"


Calculation::Calculation() {
  
}

void Calculation::Init() {

}

void Calculation::Loop(SystemState &state) {
  if(state.SensorReadingsReady) {
    CalcPitchRollYaw(state.CurrentDataPoint);
  }
}

void Calculation::CalcPitchRollYaw(DataPoint &dataPoint) {
  if(DEBUG) Serial.println("BEGIN Calculation::CalcPitchRollYaw()");
  float gyroScale = 0.001;
  filter.updateIMU(dataPoint.G_X * gyroScale, dataPoint.G_Y * gyroScale, dataPoint.G_Z * gyroScale, dataPoint.Acc_X, dataPoint.Acc_Y, dataPoint.Acc_Z);
  dataPoint.Roll = filter.getRoll();
  dataPoint.Pitch = filter.getPitch();
  dataPoint.Yaw = filter.getYaw();
  if(DEBUG) Serial.println("END Calculation::CalcPitchRollYaw()");
}