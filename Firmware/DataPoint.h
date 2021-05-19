#line 1 "E:\\AdAstra\\adastra-evo\\Firmware\\DataPoint.h"
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
  
  float PressureDelta;
  float KalmanPressureDelta;

  float Altitude;
  
  float KalmanPressure;
  float KalmanAltitude;
  float KalmanTemperature;
};