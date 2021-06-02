import 'package:evo_client/model/bluetooth_command.dart';
import 'package:evo_client/provider/bluetooth.dart';
import 'package:evo_client/components/LabeledCheckboxTile.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DeviceFlightPage extends StatefulWidget {
  DeviceFlightPage({Key? key, required this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;


  @override
  _DeviceFlightPageState createState() => _DeviceFlightPageState();
}

class _DeviceFlightPageState extends State<DeviceFlightPage> {
  bool _continuityAccepted = false;

  void onChanged(bool newValue) {
    setState(() {
      _continuityAccepted = newValue;
    });
  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    return Consumer<Bluetooth>(
        builder: (context, bluetooth, _) {
          return Scaffold(
            body:ListView(
                  children: <Widget>[
                    Card(child: LabeledCheckboxTile(label: 'One-line ListTile', value: _continuityAccepted, key: Key("cont"), padding: EdgeInsets.all(10.0), onChanged: onChanged)),
                  ]
            ),
            floatingActionButton: FloatingActionButton(
              onPressed: () => { bluetooth.sendCommand(new BluetoothCommand(type: BluetoothCommandType.Launch)) },
              tooltip: 'Increment',
              backgroundColor: bluetooth.isScanning ? Colors.redAccent : Colors.blueAccent,
              child: Icon(bluetooth.isScanning ? Icons.cancel : Icons.search),
            ), // This trailing comma makes auto-formatting nicer for build methods.
          );
        });
  }
}
