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
    UpdateKalmanFilters();
    State.CurrentDataPoint.Altitude = CalculateAltitude(State.Settings.LaunchAltitude, State.Settings.PressureNN, State.CurrentDataPoint.Pressure, (State.CurrentDataPoint.Temperature + State.CurrentDataPoint.Back_Temperature) / 2);
    UpdateHighestAltitude();
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

void Calculation::UpdateKalmanFilters() {
  State.CurrentDataPoint.KalmanPressure = PressureKalmanFilter.updateEstimate(State.CurrentDataPoint.Pressure);
}

void Calculation::UpdateHighestAltitude() {
  if(State.CurrentDataPoint.Altitude > State.HeighestAltitude) {
    State.HeighestAltitude = State.CurrentDataPoint.Altitude;
  }
}

float Calculation::CalculateAltitude(float launchAltitude, float launchPressure, float P, float T) {
  float P0 = ReadP0(launchAltitude, launchPressure);
  return ( ( ( pow( ( P0 / P ), ( 1/5.257 ) ) ) - 1 ) * ( T + 273.15 ) ) / 0.0065;
}

float Calculation::ReadP0(float myAltitude, float abs_Pressure) {
  float p0 = abs_Pressure / pow((1.0 - ( myAltitude / 44330.0 )), 5.255);
  return p0;
}