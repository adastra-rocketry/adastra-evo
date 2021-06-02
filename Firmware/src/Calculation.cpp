#include "Calculation.h"

Calculation::Calculation(SystemState &State) : State{State}
{
}

void Calculation::Init()
{
}

void Calculation::Loop()
{
  switch (State.VehicleState)
  {
  case VehicleStateType::Idle:
  case VehicleStateType::LaunchIdle:
  case VehicleStateType::Ascending:
  case VehicleStateType::Descending:
  case VehicleStateType::Landed:
    CalcPitchRollYaw();
    break;

  case VehicleStateType::Calibrating:
  case VehicleStateType::Error:
  default:
    break;
  }
}

void Calculation::CalcPitchRollYaw()
{
  if (DEBUG)
    Serial.println("BEGIN Calculation::CalcPitchRollYaw()");

  deltat = fusion.deltatUpdate();
  fusion.MahonyUpdate(State.CurrentDataPoint.G_X * DEG_TO_RAD, State.CurrentDataPoint.G_Y * DEG_TO_RAD, State.CurrentDataPoint.G_Z * DEG_TO_RAD, State.CurrentDataPoint.Acc_X, State.CurrentDataPoint.Acc_Y, State.CurrentDataPoint.Acc_Z, deltat);
  State.CurrentDataPoint.Roll = round(fusion.getRoll());
  State.CurrentDataPoint.Pitch = round(fusion.getPitch());
  State.CurrentDataPoint.Yaw = round(fusion.getYaw());
  if (DEBUG)
    Serial.println("END Calculation::CalcPitchRollYaw()");
}