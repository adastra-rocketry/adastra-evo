import 'dart:typed_data';


import 'package:flutter/material.dart';

import 'buffer_reader.dart';

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

  static BufferReader _bufferReader = new BufferReader();

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
    _bufferReader.resetOffset();
    return new DataPoint(
      state: _bufferReader.readBuffer(data),
      timeStamp: _bufferReader.readBuffer(data, signed: false),
      pressure: _bufferReader.readBuffer(data),
      temperature: _bufferReader.readBuffer(data),
      accX: _bufferReader.readBuffer(data),
      accY: _bufferReader.readBuffer(data),
      accZ: _bufferReader.readBuffer(data),
      gX: _bufferReader.readBuffer(data),
      gY: _bufferReader.readBuffer(data),
      gZ: _bufferReader.readBuffer(data),
      magX: _bufferReader.readBuffer(data),
      magY: _bufferReader.readBuffer(data),
      magZ: _bufferReader.readBuffer(data),

      backAccX: _bufferReader.readBuffer(data),
      backAccY: _bufferReader.readBuffer(data),
      backAccZ: _bufferReader.readBuffer(data),
      backGX: _bufferReader.readBuffer(data),
      backGY: _bufferReader.readBuffer(data),
      backGZ: _bufferReader.readBuffer(data),

      backTemperature: _bufferReader.readBuffer(data),

      pitch: _bufferReader.readBuffer(data, debug: true),
      roll: _bufferReader.readBuffer(data),
      yaw: _bufferReader.readBuffer(data),

      pressureDelta: _bufferReader.readBuffer(data),
      kalmanPressureDelta: _bufferReader.readBuffer(data),
      altitude: _bufferReader.readBuffer(data),
      kalmanPressure: _bufferReader.readBuffer(data),
      kalmanAltitude: _bufferReader.readBuffer(data),
      kalmanTemperature: _bufferReader.readBuffer(data),
    );
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