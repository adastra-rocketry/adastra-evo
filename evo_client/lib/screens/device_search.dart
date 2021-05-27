import 'package:evo_client/provider/bluetooth.dart';
import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:provider/provider.dart';

class DeviceSearchPage extends StatefulWidget {
  DeviceSearchPage({Key? key, required this.title, required this.selectDevice}) : super(key: key);

  Function selectDevice;

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;

  @override
  _DeviceSearchPageState createState() => _DeviceSearchPageState();
}

class _DeviceSearchPageState extends State<DeviceSearchPage> {
  _DeviceSearchPageState() : super();

  void _deviceTap(DiscoveredDevice sr) async {
    await widget.selectDevice(sr);
    Navigator.pushNamed(context, '/deviceMain');
  }

  void _startScan() async {
    await Provider.of<Bluetooth>(context, listen: false).startScan(context);

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
          appBar: AppBar(
            // Here we take the value from the MyHomePage object that was created by
            // the App.build method, and use it to set our appbar title.
            title: Text(widget.title),
          ),
          body: DataTable(
              showCheckboxColumn: false,
              columns: const <DataColumn>[
                DataColumn(
                  label: Text(
                    'Device Name',
                    style: TextStyle(fontStyle: FontStyle.italic),
                  ),
                ), DataColumn(
                  label: Text(
                    'Signal strength',
                    style: TextStyle(fontStyle: FontStyle.italic),
                  ),
                )],
              rows: bluetooth.scanResults.where((e) => e.name.startsWith('AdAstra')).map((e) => DataRow(cells: <DataCell>[DataCell(Text(e.name), onTap: () => {_deviceTap(e) }), DataCell(Text(e.rssi.toString()), onTap: () => {_deviceTap(e) })])).toList()
          ),
          floatingActionButton: FloatingActionButton(
            onPressed: _startScan,
            tooltip: 'Increment',
            child: Icon(bluetooth.isScanning ? Icons.cancel : Icons.search),
          ), // This trailing comma makes auto-formatting nicer for build methods.
        );
      }
    );
  }
}
