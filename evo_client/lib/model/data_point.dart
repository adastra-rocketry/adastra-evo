import 'dart:typed_data';


import 'package:flutter/material.dart';

class DataPoint {
  DataPoint({
    required this.state,
    required this.timeStamp,
    required this.pressure,
    required this.temperature,
    required this.accX,
    required this.accY,
    required this.accZ,
    required this.gX,
    required this.gY,
    required this.gZ,
    required this.backAccX,
    required this.backAccY,
    required this.backAccZ,
    required this.backGX,
    required this.backGY,
    required this.backGZ,
    required this.backTemperature,
    required this.magX,
    required this.magY,
    required this.magZ,
    required this.pitch,
    required this.roll,
    required this.yaw,
    required this.pressureDelta,
    required this.kalmanPressureDelta,
    required this.altitude,
    required this.kalmanPressure,
    required this.kalmanAltitude,
    required this.kalmanTemperature,
  }) : super();

  static int _offset = 0;
  int? state;
  int? timeStamp;
  double? pressure;
  double? temperature;
  double? accX;
  double? accY;
  double? accZ;
  double? gX;
  double? gY;
  double? gZ;
  double? magX;
  double? magY;
  double? magZ;
  double? backAccX;
  double? backAccY;
  double? backAccZ;
  double? backGX;
  double? backGY;
  double? backGZ;
  double? backTemperature;
  int? pitch;
  int? roll;
  int? yaw;
  double? pressureDelta;
  double? kalmanPressureDelta;
  double? altitude;
  double? kalmanPressure;
  double? kalmanAltitude;
  double? kalmanTemperature;

  static DataPoint create(List<int> list) {
    var data = new Uint8List.fromList(list).buffer.asByteData(); // Buffer bytes from list
    _offset = 0;
    return new DataPoint(
      state: _readBuffer(data),
      timeStamp: _readBuffer(data, signed: false),
      pressure: _readBuffer(data),
      temperature: _readBuffer(data),
      accX: _readBuffer(data),
      accY: _readBuffer(data),
      accZ: _readBuffer(data),
      gX: _readBuffer(data),
      gY: _readBuffer(data),
      gZ: _readBuffer(data),
      magX: _readBuffer(data),
      magY: _readBuffer(data),
      magZ: _readBuffer(data),

      backAccX: _readBuffer(data),
      backAccY: _readBuffer(data),
      backAccZ: _readBuffer(data),
      backGX: _readBuffer(data),
      backGY: _readBuffer(data),
      backGZ: _readBuffer(data),

      backTemperature: _readBuffer(data),

      pitch: _readBuffer(data, debug: true),
      roll: _readBuffer(data),
      yaw: _readBuffer(data),

      pressureDelta: _readBuffer(data),
      kalmanPressureDelta: _readBuffer(data),
      altitude: _readBuffer(data),
      kalmanPressure: _readBuffer(data),
      kalmanAltitude: _readBuffer(data),
      kalmanTemperature: _readBuffer(data),
    );
  }

  static T? _readBuffer<T>(ByteData b, {int size=4, bool signed=true, bool debug=false}) {
    T? value;

    switch (T) {
      case int:
        switch (size) {
          case 4:
            if(signed) {
              value = b.getInt32(_offset, Endian.little) as T;
            }
            else {
              value = b.getUint32(_offset, Endian.little) as T;
            }
            break;
          case 2:
            if(signed) {
              value = b.getInt16(_offset, Endian.little) as T;
            }
            else {
              value = b.getUint16(_offset, Endian.little) as T;
            }
            break;
        }
        break;
      case double:
        if(debug) {
          print(b.buffer.asInt8List(_offset, 4));
        }
        value = b.getFloat32(_offset, Endian.little) as T;
        break;
    }

    _offset = _offset + 4; // Offset is always 4 - regardless of data type
    return value;
  }

  Map<String, String> asMap() {
    var map = new Map<String, String>();
    map["State"] = state == null ? "" : state.toString();
    map["Timestamp"] = timeStamp == null ? "" : timeStamp.toString();

    map["Pressure"] = pressure == null ? "" : pressure.toString();
    map["Temperature"] = temperature == null ? "" : temperature.toString();

    map["Altitude"] = altitude == null ? "" : altitude.toString();
    map["Kalman Altitude"] = kalmanAltitude == null ? "" : kalmanAltitude.toString();
    map["Kalman Temperature"] = kalmanTemperature == null ? "" : kalmanTemperature.toString();

    map["Pitch"] = pitch == null ? "" : pitch.toString();
    map["Roll"] = roll == null ? "" : roll.toString();
    map["Yaw"] = yaw == null ? "" : yaw.toString();

    map["Acceleration X"] = accX == null ? "" : accX.toString();
    map["Acceleration Y"] = accY == null ? "" : accY.toString();
    map["Acceleration Z"] = accZ == null ? "" : accZ.toString();
    map["Gyro X"] = gX == null ? "" : gX.toString();
    map["Gyro Y"] = gY == null ? "" : gY.toString();
    map["Gyro Z"] = gZ == null ? "" : gZ.toString();
    map["Compass X"] = gX == null ? "" : gX.toString();
    map["Compass Y"] = gY == null ? "" : gY.toString();
    map["Compass Z"] = gZ == null ? "" : gZ.toString();


    map["Backup Acceleration X"] = backAccX == null ? "" : backAccX.toString();
    map["Backup Acceleration Y"] = backAccY == null ? "" : backAccY.toString();
    map["Backup Acceleration Z"] = backAccZ == null ? "" : backAccZ.toString();
    map["Backup Gyro X"] = backGX == null ? "" : backGX.toString();
    map["Backup Gyro Y"] = backGY == null ? "" : backGY.toString();
    map["Backup Gyro Z"] = backGZ == null ? "" : backGZ.toString();

    map["Backup Temperature"] = backTemperature == null ? "" : backTemperature.toString();

    map["Pressure Delta"] = pressureDelta == null ? "" : pressureDelta.toString();
    map["Kalman Pressure Delta"] = kalmanPressureDelta == null ? "" : kalmanPressureDelta.toString();
    map["Kalman Pressure"] = kalmanPressure == null ? "" : kalmanPressure.toString();
    return map;
  }
}