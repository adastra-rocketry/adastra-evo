#include "Sensors.h"

Sensors::Sensors(SystemState &state) : State{ state } {
}

void Sensors::Init() {
  if(DEBUG) Serial.println("BEGIN Sensors::Init()");
  Wire.setClock(400000);
  Wire.begin();
  InitMPU6050();
  InitIMU();
  InitBarometer();

  if(DEBUG) Serial.println("END Sensors::Init()");
}

void Sensors::InitBarometer() {
  if (!lps35hw.begin_I2C(0x5D, &Wire)) {
    if(DEBUG) Serial.println("Failed to initialize pressure sensor!");
    while (1) {}
  }
  lps35hw.setDataRate(LPS35HW_RATE_25_HZ);
}

void Sensors::InitIMU() {
  if (!lsm6ds.begin_I2C()) {
    Serial.println("Failed to find LSM6DS chip");
    while (1) {
      delay(10);
    }
  }
  lsm_temp = lsm6ds.getTemperatureSensor();
  lsm_accel = lsm6ds.getAccelerometerSensor();
  lsm_gyro = lsm6ds.getGyroSensor();
}

void Sensors::InitMPU6050() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    BackupIMUAvailable = false;
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }
}

void Sensors::Loop() {
  if(DEBUG) Serial.println("BEGIN Sensors::Loop()");
  digitalWrite(GREEN_LED, HIGH);

  // Update DataPoint
  State.CurrentDataPoint.State = State.VehicleState;
  State.CurrentDataPoint.Timestamp = millis();  

  //read pressure
  State.CurrentDataPoint.Pressure = ReadPressure();

  // read IMU
  ReadAcceleration(State.CurrentDataPoint.Acc_X, State.CurrentDataPoint.Acc_Y, State.CurrentDataPoint.Acc_Z);
  ReadGyroscope(State.CurrentDataPoint.G_X, State.CurrentDataPoint.G_Y, State.CurrentDataPoint.G_Z);
  ReadTemperature(State.CurrentDataPoint.Temperature);

  // read backup IMU if available
  if(BackupIMUAvailable) {
    ReadMPU6050(

      State.CurrentDataPoint.Back_Acc_X, 
      State.CurrentDataPoint.Back_Acc_Y, 
      State.CurrentDataPoint.Back_Acc_Z, 
      State.CurrentDataPoint.Back_G_X, 
      State.CurrentDataPoint.Back_G_Y, 
      State.CurrentDataPoint.Back_G_Z, 
      State.CurrentDataPoint.Back_Temperature
    );
  }
  digitalWrite(GREEN_LED, LOW);
  if(DEBUG) Serial.println("END Sensors::Loop()");
}

void Sensors::ReadMPU6050(float &acc_x, float &acc_y, float &acc_z, float &g_x, float &g_y, float &g_z, float &temperature) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadMPU6050()");
  mpu.getEvent(&a, &g, &temp);
  acc_x = a.acceleration.x;
  acc_y = a.acceleration.y;
  acc_z = a.acceleration.z;
  g_x = g.gyro.x;
  g_y = g.gyro.y;
  g_z = g.gyro.z;
  temperature = temp.temperature / 340.0 + 36.53;
  if(DEBUG) Serial.println("END Sensors::ReadMPU6050()");
}

void Sensors::ReadAcceleration(float &acc_x, float &acc_y, float &acc_z ) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadAcceleration()");
  lsm_accel->getEvent(&a);
  acc_x = a.acceleration.x;
  acc_y = a.acceleration.y;
  acc_z = a.acceleration.z;
  if(DEBUG) Serial.println("END Sensors::ReadAcceleration()");
}

void Sensors::ReadGyroscope(float &g_x, float &g_y, float &g_z) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadGyroscope()");
  lsm_gyro->getEvent(&g);
  g_x = g.gyro.x;
  g_y = g.gyro.y;
  g_z = g.gyro.z;
  if(DEBUG) Serial.println("END Sensors::ReadGyroscope()");
}

void Sensors::ReadTemperature(float &t) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadTemperature()");
  lsm_temp->getEvent(&temp);
  t = temp.temperature;
  if(DEBUG) Serial.println("END Sensors::ReadTemperature()");
}

float Sensors::ReadPressure() {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadPressure()");
  return lps35hw.readPressure();
}