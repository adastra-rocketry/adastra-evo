using Evo_App.Models;
using Evo_App.Views;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Plugin.BLE;
using Evo_App.Services;

namespace Evo_App.ViewModels
{
    public class SelectBluetoothDevicePageViewModel : BaseViewModel
    {
        public ObservableCollection<Plugin.BLE.Abstractions.Contracts.IDevice> Devices { get; }

        public Command ScanForDevicesCommand { get; }
        public Command<Plugin.BLE.Abstractions.Contracts.IDevice> ItemTapped { get; }

        public SelectBluetoothDevicePageViewModel()
        {
            ItemTapped = new Command<Plugin.BLE.Abstractions.Contracts.IDevice>(OnDeviceSelected);
            ScanForDevicesCommand = new Command(async () => await ExecuteScanForDevicesCommand());
            BluetoothService = DependencyService.Get<IBluetoothService>();
            Devices = BluetoothService.Devices;
        }

        async Task ExecuteScanForDevicesCommand()
        {
            IsBusy = true;

            try
            {
                BluetoothService.StartScan();

            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex);
            }
            finally
            {
                IsBusy = false;
            }
        }



        async void OnDeviceSelected(Plugin.BLE.Abstractions.Contracts.IDevice device)
        {
            if (device == null)
                return;

            // This will push the ItemDetailPage onto the navigation stack
            await Shell.Current.GoToAsync($"{nameof(ItemDetailPage)}?{nameof(ItemDetailViewModel.ItemId)}={device.Id}");
        }

        public void OnAppearing()
        {
            IsBusy = true;
        }
    }
}
