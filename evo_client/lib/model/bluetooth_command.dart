import 'dart:convert';
import 'dart:typed_data';

enum BluetoothCommandType {
  Reset,
  Launch,
  Settings

}

class BluetoothCommand {
  BluetoothCommand({required this.type, this.arg1, this.arg2, this.arg3});

  BluetoothCommandType type;
  double? arg1;
  double? arg2;
  String? arg3;

  Int8List asBytes() {
    var bdata = new ByteData(28);

    switch(type) {
      case BluetoothCommandType.Reset:
        bdata.setInt8(0, 114);
        break;
      case BluetoothCommandType.Settings:
        bdata.setInt8(0, 115);
        break;
      case BluetoothCommandType.Launch:
        bdata.setInt8(0, 108);
        break;
    }

    if(arg1 != null) bdata.setFloat32(4, arg1 as double, Endian.little);
    if(arg2 != null) bdata.setFloat32(8, arg2 as double, Endian.little);
    if(arg3 != null) {
      var data = utf8.encode(arg3 as String);
      if(data.length <= 16) {
        for (var i = 0; i < data.length; i++) {
          int byte = data[i];
          bdata.setInt8(12 + i, byte);
        }
      }
    }
    return bdata.buffer.asInt8List(0, bdata.lengthInBytes);
  }

}