/*
  Sensors.h
*/
#pragma once

#include "Arduino.h"
#include "SystemState.h"
#include "Settings.h"
#include <Adafruit_HTS221.h>
#include <Wire.h>
#include "Adafruit_LPS35HW.h"
#include <Arduino_LSM9DS1.h>
#include <Adafruit_Sensor.h>

class Sensors
{
  public:
    Sensors();
    void Init();
    void Loop(SystemState &state);
  private:
    Adafruit_LPS35HW lps35hw;
    Adafruit_HTS221 hts;
    void InitBarometer();
    void InitIMU();
    void InitTemperatureAndHumidity();
    float ReadPressure();
    void ReadTemperatureAndHumidity(float& temp, float &humidity);
    void ReadAcceleration(float &acc_x, float &acc_y, float &acc_z);
    void ReadGyroscope(float &g_x, float &g_y, float &g_z);
    void ReadMagneticField(float &m_x, float &m_y, float &m_z);   

};
