import 'package:evo_client/provider/bluetooth.dart';
import 'package:evo_client/screens/device_current_state.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class DeviceMainPage extends StatefulWidget {
  DeviceMainPage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  _DeviceMainPageState createState() => _DeviceMainPageState();
}

class _DeviceMainPageState extends State<DeviceMainPage> {
  int _currentIndex = 0;
  final List<Widget> _children = [
    DeviceCurrentStatePage(title: 'Status'),
    DeviceCurrentStatePage(title: 'Settings')
  ];


  @override
  void initState() {
    super.initState();
  }

  @override
  void deactivate() async {
    await Provider.of<Bluetooth>(context, listen: false).disconnectFromCurrentDevice();
    super.deactivate();

  }

  void onTabTapped(int index) {
    setState(() {
      _currentIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: Text(widget.title),
      ),
      body: _children[_currentIndex],
      bottomNavigationBar: BottomNavigationBar(
        onTap: onTabTapped, // new
        currentIndex: _currentIndex, // new
        items: [
          BottomNavigationBarItem(
            icon: new Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: new Icon(Icons.mail),
            label: 'Messages',
          ),
        ],
      ),
    );
  }
}
