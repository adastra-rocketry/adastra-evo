using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Evo_App.Services
{
    public interface IBluetoothService
    {
        void StartScan();
        void StopScan();

        ObservableCollection<Plugin.BLE.Abstractions.Contracts.IDevice> Devices {get; }
    }
}
