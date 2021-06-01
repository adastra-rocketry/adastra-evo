#include "Sensors.h"

Sensors::Sensors() {
  
}

void Sensors::Init() {
  if(DEBUG) Serial.println("BEGIN Sensors::Init()");
  Wire1.setClock(1000000);
  InitIMU();
  InitMPU6050();
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

void Sensors::InitMPU6050() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
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

  // Update DataPoint
  state.CurrentDataPoint.State = state.VehicleState;
  state.CurrentDataPoint.Timestamp = millis();
  state.CurrentDataPoint.Pressure = ReadPressure();
  float humidity;
  ReadTemperatureAndHumidity(state.CurrentDataPoint.Temperature, humidity);
  ReadAcceleration(state.CurrentDataPoint.Acc_X, state.CurrentDataPoint.Acc_Y, state.CurrentDataPoint.Acc_Z);
  ReadGyroscope(state.CurrentDataPoint.G_X, state.CurrentDataPoint.G_Y, state.CurrentDataPoint.G_Z);
  ReadMagneticField(state.CurrentDataPoint.Mag_X, state.CurrentDataPoint.Mag_Y, state.CurrentDataPoint.Mag_Z);
  ReadMPU6050(state.CurrentDataPoint.Back_Acc_X, state.CurrentDataPoint.Back_Acc_Y, state.CurrentDataPoint.Back_Acc_Z, state.CurrentDataPoint.Back_G_X, state.CurrentDataPoint.Back_G_Y, state.CurrentDataPoint.Back_G_Z, state.CurrentDataPoint.Back_Temperature);
  digitalWrite(GREEN_LED, LOW);
  if(DEBUG) Serial.println("END Sensors::Loop()");
}

void Sensors::ReadMPU6050(float &acc_x, float &acc_y, float &acc_z, float &g_x, float &g_y, float &g_z, float &temp) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadMPU6050()");
  mpu.getEvent(&mpu_a, &mpu_g, &mpu_temp);
  acc_x = mpu_a.acceleration.x;
  acc_y = mpu_a.acceleration.y;
  acc_z = mpu_a.acceleration.z;
  g_x = mpu_g.gyro.x;
  g_y = mpu_g.gyro.y;
  g_z = mpu_g.gyro.z;
  temp = mpu_temp.temperature;
  if(DEBUG) Serial.println("END Sensors::ReadMPU6050()");
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
  if (IMU.magneticFieldAvailable()) {
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
  hts.getEvent(&temp_reading, &humidity_reading);

  temp = temp_reading.temperature;
  humidity = humidity_reading.relative_humidity;
  if(DEBUG) Serial.println("END Sensors::ReadTemperatureAndHumidity()");
}