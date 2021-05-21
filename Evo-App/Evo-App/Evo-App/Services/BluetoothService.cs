using Plugin.BLE;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Text;

namespace Evo_App.Services
{
    public class BluetoothService : IBluetoothService
    {
        private Plugin.BLE.Abstractions.Contracts.IAdapter Adapter;

        public ObservableCollection<Plugin.BLE.Abstractions.Contracts.IDevice> Devices { get; }

        public BluetoothService()
        {

            Devices = new ObservableCollection<Plugin.BLE.Abstractions.Contracts.IDevice>();
            var ble = CrossBluetoothLE.Current;
            Adapter = CrossBluetoothLE.Current.Adapter;
            Adapter.ScanMode = Plugin.BLE.Abstractions.Contracts.ScanMode.LowLatency;
            Adapter.ScanTimeout = 60;
            var state = ble.State;
            ble.StateChanged += (s, e) =>
            {
                Debug.WriteLine($"The bluetooth state changed to {e.NewState}");
            };
        }

        public async void StartScan()
        {
            Devices.Clear();
            Adapter.DeviceDiscovered += BluetoothService_DeviceDiscovered;
            await Adapter.StartScanningForDevicesAsync();
        }

        public async void StopScan()
        {
            Adapter.DeviceDiscovered -= BluetoothService_DeviceDiscovered;
            await Adapter.StopScanningForDevicesAsync();
        }

        private void BluetoothService_DeviceDiscovered(object sender, Plugin.BLE.Abstractions.EventArgs.DeviceEventArgs e)
        {
            if (!Devices.Contains(e.Device))
            {
                Devices.Add(e.Device);
            }
        }


    }
}
