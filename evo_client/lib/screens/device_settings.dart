import 'package:evo_client/model/bluetooth_command.dart';
import 'package:evo_client/model/settings.dart';
import 'package:evo_client/provider/bluetooth.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DeviceSettingsPage extends StatefulWidget {
  DeviceSettingsPage({Key? key, required this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;


  @override
  _DeviceSettingsPageState createState() => _DeviceSettingsPageState();
}

class _DeviceSettingsPageState extends State<DeviceSettingsPage> {

  Settings? _settings;
  late TextEditingController _nameController;

  void initState() {
    super.initState();
    _nameController = TextEditingController(text: _settings != null ? _settings?.name as String : "");
    writeSettings();
    loadSettings();
  }

  @override
  void dispose() {
    _nameController.dispose();
    super.dispose();
  }


  Future<void> loadSettings() async {

    _settings = await Provider.of<Bluetooth>(context, listen: false).readSettings();
  }

  Future<void> writeSettings() async {
    await Provider.of<Bluetooth>(context, listen: false).sendCommand(new BluetoothCommand(type: BluetoothCommandType.Settings, arg1: 123.0, arg2: 321.0, arg3: "Test"));
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
            body: SingleChildScrollView(
                scrollDirection: Axis.vertical,
                child:
                DataTable(
                    columns: <DataColumn>[
                      DataColumn(label:Text("Setting",style: TextStyle(fontWeight: FontWeight.bold),)),
                      DataColumn(label:Text("Value",style: TextStyle(fontWeight: FontWeight.bold),)),
                    ],
                    rows: [
                      DataRow(
                        cells: <DataCell>[
                          DataCell(Text('Name')),
                          DataCell(TextField(
                            controller: _nameController,
                          ),
                          )],
                      ),
                      DataRow(
                        cells: <DataCell>[
                          DataCell(Text('LaunchAltitude')),
                          DataCell(Text(_settings != null ? _settings?.launchAltitude.toString() as String : "")),
                        ],
                      ),
                      DataRow(
                        cells: <DataCell>[
                          DataCell(Text('Air Pressure')),
                          DataCell(Text(_settings != null ? _settings?.pressureNN.toString() as String : "")),
                        ],
                      ),
                    ]
                )
            )
          );
        });
  }
}
