#include "Calculation.h"
#include "SystemState.h"
#include "DataPoint.h"
#include "VehicleStateType.h"


Calculation::Calculation() {
  
}

void Calculation::Init() {
}

void Calculation::Loop(SystemState &state) {
  switch (state.VehicleState) {
    case VehicleStateType::Idle:
    case VehicleStateType::LaunchIdle:
    case VehicleStateType::Ascending:
    case VehicleStateType::Descending:
    case VehicleStateType::Landed:
      CalcPitchRollYaw(state.CurrentDataPoint);
      break;
    
    case VehicleStateType::Calibrating:
    case VehicleStateType::Error:
    default:
      break;

  }
}

void Calculation::CalcPitchRollYaw(DataPoint &dataPoint) {
  if(DEBUG) Serial.println("BEGIN Calculation::CalcPitchRollYaw()");
  
  deltat = fusion.deltatUpdate();
  fusion.MahonyUpdate(dataPoint.G_X * DEG_TO_RAD, dataPoint.G_Y * DEG_TO_RAD, dataPoint.G_Z * DEG_TO_RAD, dataPoint.Acc_X, dataPoint.Acc_Y, dataPoint.Acc_Z, deltat);
  dataPoint.Roll = round(fusion.getRoll());
  dataPoint.Pitch = round(fusion.getPitch());
  dataPoint.Yaw = round(fusion.getYaw());
  if(DEBUG) Serial.println("END Calculation::CalcPitchRollYaw()");
}