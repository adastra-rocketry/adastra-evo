import 'dart:convert';
import 'dart:typed_data';

enum BluetoothCommandType {
  Reset,
  Launch,
  Settings

}

class BluetoothCommand {
  BluetoothCommand({required this.type, this.Arg1, this.Arg2, this.Arg3});

  BluetoothCommandType type;
  double? Arg1;
  double? Arg2;
  String? Arg3;

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

    if(Arg1 != null) bdata.setFloat32(4, Arg1 as double, Endian.little);
    if(Arg2 != null) bdata.setFloat32(8, Arg2 as double, Endian.little);
    if(Arg3 != null) {
      var data = utf8.encode(Arg3 as String);
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