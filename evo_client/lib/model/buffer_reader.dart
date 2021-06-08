import 'dart:typed_data';

import 'package:flutter/foundation.dart';

class BufferReader {
  int _offset = 0;

  void resetOffset() {
    _offset = 0;
  }

  T? readBuffer<T>(ByteData b, {int size=4, bool signed=true, bool debug=false}) {
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
        value = b.getFloat32(_offset, Endian.little) as T;
        break;
      case String:
        value = String.fromCharCodes(b.buffer.asInt8List(_offset, size)) as T;
        break;
    }

    _offset = _offset + 4; // Offset is always 4 - regardless of data type
    return value;
  }
}

