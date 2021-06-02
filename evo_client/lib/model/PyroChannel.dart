import 'dart:typed_data';


import 'package:flutter/material.dart';

class PyroChannel {
  PyroChannel({
    required this.pyroChannel1Continuity,
    required this.pyroChannel2Continuity,
  }) : super();

  static int _offset = 0;
  bool pyroChannel1Continuity;
  bool pyroChannel2Continuity;

  static PyroChannel create(List<int> list) {
    var data = new Uint8List.fromList(list).buffer.asByteData(); // Buffer bytes from list
    _offset = 0;
    return new PyroChannel(
      pyroChannel1Continuity: _readBuffer(data),
      pyroChannel2Continuity: _readBuffer(data),
    );
  }

  static T? _readBuffer<T>(ByteData b, {int size=4, bool signed=true, bool debug=false}) {
    T? value;

    switch (T) {
      case bool:
        value = b.getUint32(_offset, Endian.little) as T;
        break;
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

  Map<String, bool> asMap() {
    var map = new Map<String, bool>();
    map["Pyro1"] = pyroChannel1Continuity;
    map["Pyro2"] = pyroChannel2Continuity;
    return map;
  }
}