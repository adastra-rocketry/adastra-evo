#include "Sensors.h"

Sensors::Sensors() {
  
}

void Sensors::Init() {
  InitIMU();
  InitTemperatureSensor();
  InitBarometer();
}



void Sensors::InitBarometer() {
  delay(500);
  if (!BARO.begin()) {
    if(DEBUG) Serial.println("Failed to initialize pressure sensor!");
    BARO.end();
    InitBarometer();
  }
}

void Sensors::InitIMU() {
  delay(500);
  if (!IMU.begin()) {
    if(DEBUG) Serial.println("Failed to initialize IMU!");
    IMU.end();
    InitIMU();
  }
}

void Sensors::InitTemperatureSensor() {
  delay(1000);
  if (!HTS.begin()) {
    if(DEBUG) Serial.println("Failed to init temperature sensor!");
    HTS.end();
    InitTemperatureSensor();
  } else {
    float temperature = ReadTemperature();
    if(DEBUG) {
      Serial.print("Initial Temperature: ");
      Serial.println(temperature);
    }
    
    if(temperature == 0.00f) {
      HTS.end();
      if(DEBUG) Serial.println("Temperature sensor reads strange values!");
      InitTemperatureSensor();
    }
  }
}

void Sensors::Loop(SystemState &state) {
  float temperature = ReadTemperature();
  float pressure = ReadPressure();
  float acc_x, acc_y, acc_z;
  ReadAcceleration(acc_x, acc_y, acc_z);
  float g_x, g_y, g_z;
  ReadGyroscope(g_x, g_y, g_z);
  DataPoint newItem = {state.VehicleState, millis(), pressure, temperature, acc_x, acc_y, acc_z, g_x, g_y, g_z};
  state.CurrentDataPoint = newItem;
}

void Sensors::ReadAcceleration(float &acc_x, float &acc_y, float &acc_z ) {
  acc_x = -999, acc_y = -999, acc_z = -999;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(acc_x,acc_y,acc_z);
  }
}

void Sensors::ReadGyroscope(float &g_x, float &g_y, float &g_z) {
  g_x = -999, g_y = -999, g_z = -999;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(g_x,g_y,g_z);
  }
}

float Sensors::ReadPressure() {
  return BARO.readPressure();
}

float Sensors::ReadTemperature() {
  return HTS.readTemperature();
}