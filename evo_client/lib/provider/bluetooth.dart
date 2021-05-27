import 'dart:async';
import 'dart:collection';

import 'package:evo_client/model/data_point.dart';
import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

class Bluetooth extends ChangeNotifier {
  /// Internal, private state of the cart.
  DataPoint? _currentDataPoint;
  BluetoothCharacteristic? characteristic;
  BluetoothDevice? _currentBluetoothDevice;
  StreamSubscription? characteristicSubscription;

  bool _isScanning = false;
  List<ScanResult> _scanResults = [];
  StreamSubscription<List<ScanResult>>? _scanSubscription;

  /// An unmodifiable view of the items in the cart.
  DataPoint? get currentDataPoint => _currentDataPoint;
  List<ScanResult> get scanResults => _scanResults;
  bool get isScanning => _isScanning;

  void startScan() async {
    FlutterBlue flutterBlue = FlutterBlue.instance;
    _scanResults.clear();
    _isScanning = true;
    notifyListeners();

    _scanSubscription = flutterBlue.scanResults.listen((results) {
      // do something with scan results
      for (ScanResult r in results) {
        if(!_scanResults.contains(r)) {
            _scanResults.add(r);
            notifyListeners();
        }
      }
    });

    await flutterBlue.startScan(timeout: Duration(seconds: 4));

    // Stop scanning
    await stopScan();
    notifyListeners();
  }

  Future<void> stopScan() async {
    FlutterBlue flutterBlue = FlutterBlue.instance;
    await flutterBlue.stopScan();

    await _scanSubscription?.cancel();
    _scanSubscription = null;

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

  void _subscriptionError(Object error) {
    print(error);
  }

  Future<void> connectToSelectedDevice(BluetoothDevice device) async {
    await disconnectFromCurrentDevice();
    _currentBluetoothDevice = device;
    _currentBluetoothDevice?.state.listen((event) {
      print(event);
    });
    await device.connect(timeout: new Duration(seconds: 5));
    await device.requestMtu(185);
    List<BluetoothService> services = await device.discoverServices();
    services.where((s) => s.uuid == new Guid('0000181c-0000-1000-8000-00805f9b34fb')).forEach((service) async {
      var characteristics = service.characteristics;
      for(BluetoothCharacteristic c in characteristics.where((c) => c.uuid == new Guid('00002ac2-0000-1000-8000-00805f9b34fb'))) {
        characteristic = c;
        characteristicSubscription = characteristic?.value.listen(_parseNewDataPoint, onError: _subscriptionError, cancelOnError: false);
        await characteristic?.setNotifyValue(true);
      }
    });

    notifyListeners();
  }

  Future<void> disconnectFromCurrentDevice() async {
    characteristicSubscription?.cancel();
    characteristicSubscription = null;
    characteristic = null;
    _currentDataPoint = null;
    await _currentBluetoothDevice?.disconnect();
    _currentBluetoothDevice = null;
    notifyListeners();
  }
}