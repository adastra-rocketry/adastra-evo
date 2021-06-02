#include "Sensors.h"

Sensors::Sensors(SystemState &state) : State{ state } {
}

void Sensors::Init() {
  if(DEBUG) Serial.println("BEGIN Sensors::Init()");
  Wire1.setClock(400000);
  StartSensors();
  Wire.begin();
  InitMPU6050(); // not affected by I2C bug

  if(DEBUG) Serial.println("END Sensors::Init()");
}

void Sensors::StartSensors() {
  Serial.println("(re)starting sensors");
  State.Leds.setRedLED(HIGH);
  digitalWrite(PIN_ENABLE_SENSORS_3V3, HIGH);
  digitalWrite(PIN_ENABLE_I2C_PULLUP, HIGH);
  Wire1.begin();
  InitIMU();
  InitTemperatureAndHumidity();
  InitBarometer();
  Wire1Stopped = false;
  State.Leds.setRedLED(LOW);
}

void Sensors::StopSensors() {
  digitalWrite(PIN_ENABLE_SENSORS_3V3, LOW);
  digitalWrite(PIN_ENABLE_I2C_PULLUP, LOW);
  Wire1Stopped = true;
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
    BackupIMUAvailable = false;
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }
}

void Sensors::InitTemperatureAndHumidity() {
  if (!hts.begin_I2C(0x5F, &Wire1, 0)) {
    if(DEBUG) Serial.println("Failed to init temperature sensor!");
    while (1);
  }
  hts.setDataRate(HTS221_RATE_12_5_HZ);
}

void Sensors::Loop() {
  if(DEBUG) Serial.println("BEGIN Sensors::Loop()");
  digitalWrite(GREEN_LED, HIGH);
  if(Wire1Stopped) StartSensors();

  WatchDogTimer = millis();

  // Update DataPoint
  State.CurrentDataPoint.State = State.VehicleState;
  State.CurrentDataPoint.Timestamp = millis();  

  //read pressure
  State.CurrentDataPoint.Pressure = ReadPressure();
  if(!CheckWatchDog()) return;

  // read temperature only every 10 reads
  if(loopDivider % 10 == 0) {
    float humidity;
    ReadTemperatureAndHumidity(State.CurrentDataPoint.Temperature, humidity);
    if(!CheckWatchDog()) return;
  }
  loopDivider++;

  // read IMU
  ReadAcceleration(State.CurrentDataPoint.Acc_X, State.CurrentDataPoint.Acc_Y, State.CurrentDataPoint.Acc_Z);
  if(!CheckWatchDog()) return;
  ReadGyroscope(State.CurrentDataPoint.G_X, State.CurrentDataPoint.G_Y, State.CurrentDataPoint.G_Z);
  if(!CheckWatchDog()) return;
  ReadMagneticField(State.CurrentDataPoint.Mag_X, State.CurrentDataPoint.Mag_Y, State.CurrentDataPoint.Mag_Z);
  if(!CheckWatchDog()) return;

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
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(acc_x,acc_y,acc_z);
  }
  if(DEBUG) Serial.println("END Sensors::ReadAcceleration()");
}

void Sensors::ReadGyroscope(float &g_x, float &g_y, float &g_z) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadGyroscope()");
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(g_y, g_x, g_z);   // X and Y seem to be invert and swapped
    g_x *= -1;
    g_y *= -1;
  }
  if(DEBUG) Serial.println("END Sensors::ReadGyroscope()");
}

void Sensors::ReadMagneticField(float &m_x, float &m_y, float &m_z) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadMagneticField()");
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(m_x, m_y, m_z);
  }
  if(DEBUG) Serial.println("END Sensors::ReadMagneticField()");
}

float Sensors::ReadPressure() {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadPressure()");
  return lps35hw.readPressure();
}

void Sensors::ReadTemperatureAndHumidity(float& temperature, float &humidity) {
  if(DEBUG) Serial.println("BEGIN Sensors::ReadTemperatureAndHumidity()");
  hts.getEvent(&temp, &hum);

  temperature = temp.temperature;
  humidity = hum.relative_humidity;
  if(DEBUG) Serial.println("END Sensors::ReadTemperatureAndHumidity()");
}

bool Sensors::CheckWatchDog() {
  if(millis() - WatchDogTimer > 10) {
    StopSensors();
    return false;
  }
  WatchDogTimer = millis();
  return true;
}