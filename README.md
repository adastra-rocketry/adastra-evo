# adastra-evo

[![test](https://github.com/adastra-rocketry/adastra-evo/actions/workflows/build.yml/badge.svg)](https://github.com/adastra-rocketry/adastra-evo/actions/workflows/build.yml)
[![Spell Check](https://github.com/adastra-rocketry/adastra-evo/actions/workflows/spellcheck.yml/badge.svg)](https://github.com/adastra-rocketry/adastra-evo/actions/workflows/spellcheck.yml)


## Sensor Library test with the Arduino Nano 33 BLE Sense

Sensor | Lib | Comment
--- | --- | ---
LSM9DS1 | SparkFun_LSM9DS1_Arduino_Library | Doesn't compile because of SPI specifics... Doesn't work even after removing the SPI stuff
LSM9DS1 | Arduino_LSM9DS1 | Works but has limited options
LSM9DS1 | Adafruit_LSM9DS1 | freezes the I2C Bus instantly
LPS35HW | Adafruit_LPS35HW | Works quite good
MPU6050 | Adafruit_MPU6050 | Works good and fast - calibration?
HTS221 | Adafruit_HTS221 | More options than the Arduino one