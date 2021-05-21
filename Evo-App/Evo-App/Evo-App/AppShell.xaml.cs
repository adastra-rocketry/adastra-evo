using Evo_App.ViewModels;
using Evo_App.Views;
using System;
using System.Collections.Generic;
using Xamarin.Forms;

namespace Evo_App
{
    public partial class AppShell : Xamarin.Forms.Shell
    {
        public AppShell()
        {
            InitializeComponent();
            Routing.RegisterRoute(nameof(ItemDetailPage), typeof(ItemDetailPage));
            Routing.RegisterRoute(nameof(NewItemPage), typeof(NewItemPage));
            GoToAsync("//SelectBluetoothDevicePage");
        }

    }
}
