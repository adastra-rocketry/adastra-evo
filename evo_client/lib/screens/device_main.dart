import 'dart:async';

import 'package:evo_client/model/data_point.dart';
import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

class DeviceMainPage extends StatefulWidget {
  DeviceMainPage({Key? key, required this.title, required this.device}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;
  final BluetoothDevice device;


  @override
  _DeviceMainPageState createState() => _DeviceMainPageState();
}

class _DeviceMainPageState extends State<DeviceMainPage> {
  DataPoint? dataPoint;
  BluetoothCharacteristic? characteristic;
  StreamSubscription? characteristicSubscription;

  Future<void> _connectToSelectedDevice() async {
    await _disconnectFromSelectedDevice();
    await new Future.delayed(const Duration(seconds: 1));
    await widget.device.connect(timeout: new Duration(seconds: 5));
    await new Future.delayed(const Duration(seconds: 1));
    await widget.device.requestMtu(185);
    List<BluetoothService> services = await widget.device.discoverServices();
    services.where((s) => s.uuid == new Guid('0000181c-0000-1000-8000-00805f9b34fb')).forEach((service) async {
      var characteristics = service.characteristics;
      for(BluetoothCharacteristic c in characteristics.where((c) => c.uuid == new Guid('00002ac2-0000-1000-8000-00805f9b34fb'))) {
        characteristic = c;
        await characteristic?.setNotifyValue(true);
        characteristicSubscription = characteristic?.value.listen(_parseNewDataPoint);
      }
    });
  }

  void _parseNewDataPoint(List<int> data) {
    var dp = DataPoint.create(data);
    setState(() {
      dataPoint = dp;
    });
  }

  Future<void> _disconnectFromSelectedDevice() async {
    characteristicSubscription?.cancel();
    characteristicSubscription = null;
    characteristic = null;
    await widget.device.disconnect();
  }

  @override
  void initState() {
    super.initState();
    _connectToSelectedDevice();
  }

  @override
  void deactivate() {
    super.deactivate();
    _disconnectFromSelectedDevice();
  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    var rows = <DataRow>[];
    dataPoint?.asMap().forEach((key, value) {
      rows.add(new DataRow(
          cells: <DataCell>[
            DataCell(Text(key)),
            DataCell(Text(value))
          ]
      ));
    });

    return Scaffold(
      appBar: AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: Text(widget.title),
      ),
      body: SingleChildScrollView(
        scrollDirection: Axis.vertical,
        child:
          DataTable(
            columns: <DataColumn>[
              DataColumn(label:Text("Measurement",style: TextStyle(fontWeight: FontWeight.bold),)),
              DataColumn(label:Text("Value",style: TextStyle(fontWeight: FontWeight.bold),)),
            ],
            rows: rows
          )
      ),
    );
  }
}
