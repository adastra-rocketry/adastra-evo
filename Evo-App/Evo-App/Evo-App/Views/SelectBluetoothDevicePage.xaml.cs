using Evo_App.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace Evo_App.Views
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class SelectBluetoothDevicePage : ContentPage
    {
        SelectBluetoothDevicePageViewModel _viewModel;

        public SelectBluetoothDevicePage()
        {
            InitializeComponent();
            this.BindingContext = _viewModel = new SelectBluetoothDevicePageViewModel();
        }
        protected override void OnAppearing()
        {
            base.OnAppearing();
            _viewModel.OnAppearing();
        }
    }
}