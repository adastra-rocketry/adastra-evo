import 'package:evo_client/provider/bluetooth.dart';
import 'package:evo_client/screens/device_main.dart';
import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:provider/provider.dart';
import 'screens/device_search.dart';


void main() {
  runApp(MultiProvider(
      child: MyApp(),
    providers: [
      ChangeNotifierProvider(create: (context) => Bluetooth()),
    ],
  ));
}

class MyApp extends StatefulWidget  {
  @override
  _MyAppState createState() => new _MyAppState();
}

class _MyAppState extends State<MyApp> {
  DiscoveredDevice? device;

  void selectDevice(DiscoveredDevice newDevice) async {
    await Provider.of<Bluetooth>(context, listen: false).stopScan();
    await Provider.of<Bluetooth>(context, listen: false).connectToSelectedDevice(newDevice);
    setState(() {
      device = newDevice;
    });

  }

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'AdAstra Evo',
      initialRoute: device == null ? "/deviceSelector" : "/deviceMain",
      routes: {
        '/deviceSelector': (context) => DeviceSearchPage(
          title: "Select your device",
          selectDevice: selectDevice,
        ),
        "/deviceMain": (context) => DeviceMainPage(title: device?.name as String),
      },
      theme: ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or simply save your changes to "hot reload" in a Flutter IDE).
        // Notice that the counter didn't reset back to zero; the application
        // is not restarted.
        primarySwatch: Colors.blue,
      ),
    );
  }
}