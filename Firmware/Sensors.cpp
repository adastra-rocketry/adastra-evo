#include "Sensors.h"

Sensors::Sensors() {
  
}

void Sensors::Init() {
  if(DEBUG) Serial.println("BEGIN Sensors::Init()");
  InitIMU();
  InitTemperatureSensor();
  InitBarometer();
  if(DEBUG) Serial.println("END Sensors::Init()");
}



void Sensors::InitBarometer() {
  delay(500);
  if (!lps.begin(&Wire1)) {
    if(DEBUG) Serial.println("Failed to initialize pressure sensor!");
    while (1) {}
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
  if(DEBUG) Serial.println("BEGIN Sensors::Loop()");

  long currentMillis = millis();
  if(currentMillis - previousMillis >= SAVE_INTERVAL) {  
    float temperature = ReadTemperature();
    Serial.flush();
    float pressure = ReadPressure();
    Serial.flush();
    float humidity = ReadHumidity();
    Serial.flush();
    float acc_x, acc_y, acc_z;
    ReadAcceleration(acc_x, acc_y, acc_z);
    Serial.flush();
    float g_x, g_y, g_z;
    ReadGyroscope(g_x, g_y, g_z);
    Serial.flush();
    float m_x, m_y, m_z;
    ReadMagneticField(m_x, m_y, m_z);
    Serial.flush();
    DataPoint newItem = {state.VehicleState, millis(), pressure, temperature, acc_x, acc_y, acc_z, g_x, g_y, g_z, m_x, m_y, m_z};
    Serial.flush();
    state.CurrentDataPoint = newItem;    
    Serial.flush();

    previousMillis = currentMillis;
  }
  if(DEBUG) Serial.println("END Sensors::Loop()");
}

void Sensors::ReadAcceleration(float &acc_x, float &acc_y, float &acc_z ) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadAcceleration()");
  acc_x = -999, acc_y = -999, acc_z = -999;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(acc_x,acc_y,acc_z);
  }
  if(DEBUG) Serial.println("END Sensors::ReadAcceleration()");
}

void Sensors::ReadGyroscope(float &g_x, float &g_y, float &g_z) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadGyroscope()");
  g_x = -999, g_y = -999, g_z = -999;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(g_x,g_y,g_z);
  }
  if(DEBUG) Serial.println("END Sensors::ReadGyroscope()");
}

void Sensors::ReadMagneticField(float &m_x, float &m_y, float &m_z) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadMagneticField()");
  m_x = -999, m_y = -999, m_z = -999;
  if (IMU.gyroscopeAvailable()) {
    IMU.readMagneticField(m_x, m_y, m_z);
  }
  if(DEBUG) Serial.println("END Sensors::ReadMagneticField()");
}

float Sensors::ReadPressure() {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadPressure()");
  return lps.readPressure();
}

float Sensors::ReadTemperature() {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadTemperature()");
  return HTS.readTemperature();
}

float Sensors::ReadHumidity() {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadHumidity()");
  return HTS.readHumidity();
}
