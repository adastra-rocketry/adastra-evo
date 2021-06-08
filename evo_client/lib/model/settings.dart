import 'dart:typed_data';
import 'buffer_reader.dart';

import 'package:flutter/material.dart';

class Settings {
  Settings({
    required this.launchAltitude,
    required this.pressureNN,
    required this.name
  }) : super();

  static BufferReader _bufferReader = new BufferReader();
  double? launchAltitude;
  double? pressureNN;
  String? name;

  static Settings create(List<int> list) {
    var data = new Uint8List.fromList(list).buffer.asByteData(); // Buffer bytes from list
    _bufferReader.resetOffset();
    return new Settings(
      launchAltitude: _bufferReader.readBuffer(data),
      pressureNN: _bufferReader.readBuffer(data),
      name: _bufferReader.readBuffer(data, size: 16)
    );
  }
}