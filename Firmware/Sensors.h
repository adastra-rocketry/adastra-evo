/*
  Sensors.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "Settings.h"
#include <Arduino_HTS221.h>
#include <Arduino_LSM9DS1.h>
#include <Wire.h>
#include "LPS35HW.h"

class Sensors
{
  public:
    Sensors();
    void Init();
    void Loop(SystemState &state);
  private:
    LPS35HW lps;
    void InitBarometer();
    void InitIMU();
    void InitTemperatureSensor();
    float ReadPressure();
    float ReadTemperature();
    float ReadHumidity();
    void ReadAcceleration(float &acc_x, float &acc_y, float &acc_z);
    void ReadGyroscope(float &g_x, float &g_y, float &g_z);
    void ReadMagneticField(float &m_x, float &m_y, float &m_z);

    unsigned long previousMillis = 0;

};
