/*
  Sensors.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState/SystemState.h"
#include "Settings/Settings.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LPS35HW.h>


class Sensors
{
  public:
    Sensors(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    bool BackupIMUAvailable = true;
    Adafruit_MPU6050 mpu;
    Adafruit_LSM6DS33 lsm6ds;
    Adafruit_Sensor *lsm_temp, *lsm_accel, *lsm_gyro;
    Adafruit_LPS35HW lps35hw;
    void InitBarometer();
    void InitIMU();
    void InitMPU6050();
    float ReadPressure();
    void ReadAcceleration(float &acc_x, float &acc_y, float &acc_z);
    void ReadGyroscope(float &g_x, float &g_y, float &g_z);
    void ReadTemperature(float &t);
    void ReadMPU6050(float &acc_x, float &acc_y, float &acc_z, float &g_x, float &g_y, float &g_z, float &temp);
    sensors_event_t a, g, temp, hum;
};
