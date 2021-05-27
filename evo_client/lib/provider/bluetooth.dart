import 'dart:async';
import 'dart:io';
import 'package:evo_client/model/data_point.dart';
import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:location_permissions/location_permissions.dart';

class Bluetooth extends ChangeNotifier {
  /// Internal, private state of the cart.
  final flutterReactiveBle = FlutterReactiveBle();
  DataPoint? _currentDataPoint;
  DiscoveredDevice? _currentBluetoothDevice;
  StreamSubscription? _characteristicSubscription;
  StreamSubscription<DiscoveredDevice>? _scanStream;
  StreamSubscription? _connectionStream;

  bool _isScanning = false;

  List<DiscoveredDevice> _scanResults = [];

  /// An unmodifiable view of the items in the cart.
  DataPoint? get currentDataPoint => _currentDataPoint;
  List<DiscoveredDevice> get scanResults => _scanResults;
  bool get isScanning => _isScanning;

  Future<void> startScan(BuildContext context) async {
    bool goForIt=false;
    PermissionStatus permission;
    if (Platform.isAndroid) {
      permission = await LocationPermissions().requestPermissions();
      if (permission == PermissionStatus.granted)
        goForIt=true;
    } else if (Platform.isIOS) {
      goForIt=true;
    }

    if(goForIt) {
      _scanResults.clear();
      _isScanning = true;
      notifyListeners();

      _scanStream = flutterReactiveBle.scanForDevices(withServices: [Uuid.parse('0000181c-0000-1000-8000-00805f9b34fb')], scanMode: ScanMode.lowLatency).listen((r) {
        if(_scanResults.where((element) => element.id == r.id).length == 0) {
          _scanResults.add(r);
          notifyListeners();
        }
      }, onError: (err) {
        print(err);
      });
    }
  }

  Future<void> showNoPermissionDialog(BuildContext context) async => showDialog<void>(
    context: context,
    barrierDismissible: false, // user must tap button!
    builder: (BuildContext context) => AlertDialog(
      title: const Text('No location permission '),
      content: SingleChildScrollView(
        child: ListBody(
          children: <Widget>[
            const Text('No location permission granted.'),
            const Text('Location permission is required for BLE to function.'),
          ],
        ),
      ),
      actions: <Widget>[
        TextButton(
          child: const Text('Acknowledge'),
          onPressed: () {
            Navigator.of(context).pop();
          },
        ),
      ],
    ),
  );

  Future<void> stopScan() async {
    if(_scanStream != null) _scanStream?.cancel();
    _isScanning = false;
  }

  void _parseNewDataPoint(List<int> data) {
    if(data.length > 60) {
      var dp = DataPoint.create(data);
      _currentDataPoint = dp;
      notifyListeners();
    } else {
      print('Too short package received');
    }
  }

  Future<void> connectToSelectedDevice(DiscoveredDevice device) async {
    _connectionStream = flutterReactiveBle.connectToAdvertisingDevice(
      id: device.id,
      withServices: [Uuid.parse('0000181c-0000-1000-8000-00805f9b34fb')],
      prescanDuration: const Duration(seconds: 5),
      servicesWithCharacteristicsToDiscover: { Uuid.parse('0000181c-0000-1000-8000-00805f9b34fb'): [Uuid.parse('00002ac2-0000-1000-8000-00805f9b34fb')]},
      connectionTimeout: const Duration(seconds:  2),
    ).listen((connectionState) {
      // Handle connection state updates
    }, onError: (Object error) {
      // Handle a possible error
    });

    final mtu = await flutterReactiveBle.requestMtu(deviceId: device.id, mtu: 250);
    print('set MTU to $mtu');

    final characteristic = QualifiedCharacteristic(serviceId: Uuid.parse('0000181c-0000-1000-8000-00805f9b34fb'), characteristicId: Uuid.parse('00002ac2-0000-1000-8000-00805f9b34fb'), deviceId: device.id);
    _characteristicSubscription = flutterReactiveBle.subscribeToCharacteristic(characteristic).listen((data) {
      _parseNewDataPoint(data);
    }, onError: (dynamic error) {
      // code to handle errors
    });

    notifyListeners();
  }

  Future<void> disconnectFromCurrentDevice() async {
    _characteristicSubscription?.cancel();
    _characteristicSubscription = null;
    _connectionStream?.cancel();
    _connectionStream = null;
    _currentDataPoint = null;
    _currentBluetoothDevice = null;
    notifyListeners();
  }
}