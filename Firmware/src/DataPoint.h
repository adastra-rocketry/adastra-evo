#pragma once
#include "SystemState\VehicleStateType.h"

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

  float Back_Acc_X;
  float Back_Acc_Y;
  float Back_Acc_Z;

  float Back_G_X;
  float Back_G_Y;
  float Back_G_Z;

  float Back_Temperature;

  int Pitch;
  int Roll;
  int Yaw;
  
  float PressureDelta;
  float KalmanPressureDelta;

  float Altitude;
  
  float KalmanPressure;
  float KalmanAltitude;
  float KalmanTemperature;
};