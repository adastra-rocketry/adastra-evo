import 'dart:typed_data';
import 'buffer_reader.dart';

import 'package:flutter/material.dart';

class PyroChannel {
  PyroChannel({
    required this.pyroChannel1Continuity,
    required this.pyroChannel2Continuity,
  }) : super();

  static BufferReader _bufferReader = new BufferReader();
  bool pyroChannel1Continuity;
  bool pyroChannel2Continuity;

  static PyroChannel create(List<int> list) {
    var data = new Uint8List.fromList(list).buffer.asByteData(); // Buffer bytes from list
    _bufferReader.resetOffset();
    return new PyroChannel(
      pyroChannel1Continuity: _bufferReader.readBuffer(data),
      pyroChannel2Continuity: _bufferReader.readBuffer(data),
    );
  }

  Map<String, bool> asMap() {
    var map = new Map<String, bool>();
    map["Pyro1"] = pyroChannel1Continuity;
    map["Pyro2"] = pyroChannel2Continuity;
    return map;
  }
}