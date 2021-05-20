#pragma once
#include "VehicleStateType.h"

struct DataPoint {
  VehicleStateType State;
  unsigned long Timestamp;
  float Pressure;
  float Temperature;
  float Acc_X;
  float Acc_Y;
  float Acc_Z;

  float G_X;
  float G_Y;
  float G_Z;

  float Mag_X;
  float Mag_Y;
  float Mag_Z;

  float Pitch;
  float Roll;
  float Yaw;
  
  float PressureDelta;
  float KalmanPressureDelta;

  float Altitude;
  
  float KalmanPressure;
  float KalmanAltitude;
  float KalmanTemperature;
};