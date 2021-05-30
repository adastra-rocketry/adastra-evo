#include "Calculation.h"
#include "SystemState.h"
#include <MadgwickAHRS.h>

#include "DataPoint.h"


Calculation::Calculation() {
  
}

void Calculation::Init() {

}

void Calculation::Loop(SystemState &state) {
  CalcPitchRollYaw(state.CurrentDataPoint);
}

void Calculation::CalcPitchRollYaw(DataPoint &dataPoint) {
  if(DEBUG) Serial.println("BEGIN Calculation::CalcPitchRollYaw()");
  filter.updateIMU(dataPoint.G_X, dataPoint.G_Y, dataPoint.G_Z, dataPoint.Acc_X, dataPoint.Acc_Y, dataPoint.Acc_Z);

  dataPoint.Pitch = filter.getPitch();
  dataPoint.Roll = filter.getRoll();
  dataPoint.Yaw = filter.getYaw();
  if(DEBUG) Serial.println("END Calculation::CalcPitchRollYaw()");
}