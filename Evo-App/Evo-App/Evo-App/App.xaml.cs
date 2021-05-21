using Evo_App.Services;
using Evo_App.Views;
using System;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace Evo_App
{
    public partial class App : Application
    {

        public App()
        {
            InitializeComponent();

            DependencyService.Register<IBluetoothService, BluetoothService>();
            MainPage = new AppShell();
        }

        protected override void OnStart()
        {
        }

        protected override void OnSleep()
        {
        }

        protected override void OnResume()
        {
        }
    }
}
