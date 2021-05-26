import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

class DeviceSearchPage extends StatefulWidget {
  DeviceSearchPage({Key? key, required this.title}) : super(key: key);

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
  List<ScanResult> _scanResults = [];

  _DeviceSearchPageState() : super() {
    _startScan();

  }

  void _startScan() async {
    FlutterBlue flutterBlue = FlutterBlue.instance;
    _scanResults.clear();

    var subscription = flutterBlue.scanResults.listen((results) {
      // do something with scan results
      for (ScanResult r in results) {
        if(!_scanResults.contains(r)) {
          setState(() {
            _scanResults.add(r);
          });
        }
      }
    });

    await flutterBlue.startScan(timeout: Duration(seconds: 4));

    // Stop scanning
    subscription.cancel();
    flutterBlue.stopScan();
  }

  void _deviceTap(ScanResult sr) {

  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
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
          rows: _scanResults.where((e) => e.advertisementData.localName.startsWith('AdAstra')).map((e) => DataRow(cells: <DataCell>[DataCell(Text(e.advertisementData.localName), onTap: () => {_deviceTap(e) }), DataCell(Text(e.rssi.toString()), onTap: () => {_deviceTap(e) })])).toList()
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _startScan,
        tooltip: 'Increment',
        child: Icon(Icons.search),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}
