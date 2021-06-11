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

class _MyAppState extends State<MyApp> with WidgetsBindingObserver {
  DiscoveredDevice? device;

  @override
  void initState() {
    WidgetsBinding.instance?.addObserver(this);
    super.initState();
  }

  @override
  void dispose() {
    WidgetsBinding.instance?.removeObserver(this);
    super.dispose();
  }

  @override
  void didChangeAppLifecycleState(AppLifecycleState state) async {
    var ble = Provider.of<Bluetooth>(context, listen: false);
    switch(state) {
      case AppLifecycleState.paused:
        await ble.stopScan();
        await ble.disconnectFromCurrentDevice();
        break;
      case AppLifecycleState.resumed:
        if(device != null) {
          await ble.connectToSelectedDevice();
        }
        break;

    }
    print('state = $state');
  }

  void selectDevice(DiscoveredDevice newDevice) async {
    await Provider.of<Bluetooth>(context, listen: false).stopScan();
    Provider.of<Bluetooth>(context, listen: false).setCurrentDevice(newDevice);
    await Provider.of<Bluetooth>(context, listen: false).connectToSelectedDevice();
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