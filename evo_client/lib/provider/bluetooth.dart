import 'dart:async';
import 'dart:io';
import 'package:evo_client/model/bluetooth_command.dart';
import 'package:evo_client/model/data_point.dart';
import 'package:evo_client/model/settings.dart';
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

  Future<bool> startScan() async {
    bool goForIt=false;
    PermissionStatus permission;
    if (Platform.isAndroid) {
      permission = await LocationPermissions().requestPermissions();
      if (permission == PermissionStatus.granted) {
        goForIt = true;
      }
    } else if (Platform.isIOS) {
      goForIt=true;
    }

    if(goForIt) {
      _scanResults.clear();
      _isScanning = true;
      notifyListeners();

      _scanStream = flutterReactiveBle.scanForDevices(withServices: [Uuid.parse('92aab162-79af-422f-a53b-fca7b98e2327')], scanMode: ScanMode.lowLatency).listen((r) {
        if(_scanResults.where((element) => element.id == r.id).length == 0) {
          _scanResults.add(r);
          notifyListeners();
        }
      }, onError: (err) {
        print(err);
      });
    }
    return goForIt;
  }

  Future<void> stopScan() async {
    if(_scanStream != null) _scanStream?.cancel();
    _isScanning = false;
    notifyListeners();
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

  void setCurrentDevice(DiscoveredDevice? device) {
    _currentBluetoothDevice = device;
  }

  Future<void> connectToSelectedDevice() async {
    if(_currentBluetoothDevice != null) {
      var device = _currentBluetoothDevice as DiscoveredDevice;
      _connectionStream = flutterReactiveBle.connectToAdvertisingDevice(
        id: device.id,
        withServices: [Uuid.parse('92aab162-79af-422f-a53b-fca7b98e2327')],
        prescanDuration: const Duration(seconds: 5),
        servicesWithCharacteristicsToDiscover: {
          Uuid.parse('92aab162-79af-422f-a53b-fca7b98e2327'): [
            Uuid.parse('61e8de2f-935b-42b2-ae5b-50d444b540eb')
          ]
        },
        connectionTimeout: const Duration(seconds: 2),
      ).listen((connectionState) {
        switch(connectionState.connectionState) {
          case DeviceConnectionState.disconnected:
            disconnectFromCurrentDevice();
            setCurrentDevice(null);
            notifyListeners();
            break;
          default:
            break;
        }
      }, onError: (Object error) {
        disconnectFromCurrentDevice();
        setCurrentDevice(null);
        notifyListeners();
      });

      final mtu = await flutterReactiveBle.requestMtu(
          deviceId: device.id, mtu: 250);
      print('set MTU to $mtu');

      final characteristic = getCharacteristic(
          '61e8de2f-935b-42b2-ae5b-50d444b540eb') as QualifiedCharacteristic;
      _characteristicSubscription =
          flutterReactiveBle.subscribeToCharacteristic(characteristic).listen((
              data) {
            _parseNewDataPoint(data);
          }, onError: (dynamic error) {
            // code to handle errors
          });

      notifyListeners();
    }
  }

  QualifiedCharacteristic? getCharacteristic(charGuid) {
    if(_currentBluetoothDevice != null) {
      return QualifiedCharacteristic(serviceId: Uuid.parse('92aab162-79af-422f-a53b-fca7b98e2327'), characteristicId: Uuid.parse(charGuid), deviceId: _currentBluetoothDevice?.id as String);
    } else {
      return null;
    }
  }

  Future<void> disconnectFromCurrentDevice() async {
    if(_currentBluetoothDevice != null) {
      _characteristicSubscription?.cancel();
      _characteristicSubscription = null;
      _connectionStream?.cancel();
      _connectionStream = null;
      _currentDataPoint = null;
      notifyListeners();
    }
  }

  Future<Settings> readSettings() async {
    final characteristic = getCharacteristic("da4b4a5a-bdd5-4e9f-945a-55180c8b3b87") as QualifiedCharacteristic;
    final response = await flutterReactiveBle.readCharacteristic(characteristic);
    var settings = Settings.create(response);
    return settings;
  }

  Future<void> sendCommand(BluetoothCommand command) async {
    var data = command.asBytes();
    final characteristic = getCharacteristic('da4b4a5a-bdd5-4e9f-945a-55180c8b3f53') as QualifiedCharacteristic;
    await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: data);
  }
}