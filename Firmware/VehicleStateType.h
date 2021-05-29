/*
  VehicleStateType.h - Library for storing and retrieving sensor data
*/
#pragma once

enum VehicleStateType {
  Idle = 0,
  LaunchIdle = 1,
  Ascending = 2,
  Descending = 3,
  Landed = 4,

  Error = 666
};
