#line 1 "E:\\AdAstra\\adastra-evo\\Firmware\\Sensors.h"
/*
  Sensors.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "Settings.h"
#include <Arduino_LPS22HB.h>
#include <Arduino_HTS221.h>
#include <Arduino_LSM9DS1.h>

class Sensors
{
  public:
    Sensors();
    void Init();
    void Loop(SystemState &state);
  private:
    void InitBarometer();
    void InitIMU();
    void InitTemperatureSensor();
    float ReadPressure();
    float ReadTemperature();
    void ReadAcceleration(float &acc_x, float &acc_y, float &acc_z);
    void ReadGyroscope(float &g_x, float &g_y, float &g_z);
};