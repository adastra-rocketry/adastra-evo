#include "Sensors.h"

Sensors::Sensors() {
  
}

void Sensors::Init() {
  if(DEBUG) Serial.println("BEGIN Sensors::Init()");
  InitIMU();
  InitTemperatureAndHumidity();
  InitBarometer();
  if(DEBUG) Serial.println("END Sensors::Init()");
}

void Sensors::InitBarometer() {
  if (!lps35hw.begin_I2C(0x5C, &Wire1)) {
    if(DEBUG) Serial.println("Failed to initialize pressure sensor!");
    while (1) {}
  }
  lps35hw.setDataRate(LPS35HW_RATE_25_HZ);
}

void Sensors::InitIMU() {
  if (!IMU.begin()) {
    if(DEBUG) Serial.println("Failed to initialize IMU!");
    IMU.end();
    InitIMU();
  }
}

void Sensors::InitTemperatureAndHumidity() {
  if (!hts.begin_I2C(0x5F, &Wire1, 0)) {
    if(DEBUG) Serial.println("Failed to init temperature sensor!");
    while (1);
  }
  hts.setDataRate(HTS221_RATE_12_5_HZ);
}

void Sensors::Loop(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN Sensors::Loop()");
  digitalWrite(GREEN_LED, HIGH);
  float temperature, humidity;
  ReadTemperatureAndHumidity(temperature, humidity);
  float pressure = ReadPressure();
  float acc_x, acc_y, acc_z;
  ReadAcceleration(acc_x, acc_y, acc_z);
  float g_x, g_y, g_z;
  ReadGyroscope(g_x, g_y, g_z);
  float m_x, m_y, m_z;
  ReadMagneticField(m_x, m_y, m_z);
  DataPoint newItem = {state.VehicleState, millis(), pressure, temperature, acc_x, acc_y, acc_z, g_x, g_y, g_z, m_x, m_y, m_z};
  state.CurrentDataPoint = newItem;
  digitalWrite(GREEN_LED, LOW);
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
  return lps35hw.readPressure();
}

void Sensors::ReadTemperatureAndHumidity(float& temp, float &humidity) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadTemperatureAndHumidity()");
  sensors_event_t temp_reading;
  sensors_event_t humidity_reading;
  hts.getEvent(&temp_reading, &humidity_reading);

  temp = temp_reading.temperature;
  humidity = humidity_reading.relative_humidity;
  if(DEBUG) Serial.println("END Sensors::ReadTemperatureAndHumidity()");
}