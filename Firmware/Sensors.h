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
#include <Adafruit_MPU6050.h>

class Sensors
{
  public:
    Sensors();
    void Init();
    void Loop(SystemState &state);
  private:
    int i = 0;
    bool backupIMUAvailable = true;
    Adafruit_LPS35HW lps35hw;
    Adafruit_HTS221 hts;
    Adafruit_MPU6050 mpu;
    void InitBarometer();
    void InitIMU();
    void InitMPU6050();
    void InitTemperatureAndHumidity();
    float ReadPressure();
    void ReadTemperatureAndHumidity(float& temp, float &humidity);
    void ReadAcceleration(float &acc_x, float &acc_y, float &acc_z);
    void ReadGyroscope(float &g_x, float &g_y, float &g_z);
    void ReadMagneticField(float &m_x, float &m_y, float &m_z);   
    void ReadMPU6050(float &acc_x, float &acc_y, float &acc_z, float &g_x, float &g_y, float &g_z, float &temp);

    sensors_event_t mpu_a, mpu_g, mpu_temp;
    sensors_event_t temp_reading;
    sensors_event_t humidity_reading;
};
