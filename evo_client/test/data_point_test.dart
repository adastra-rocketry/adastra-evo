// This is a basic Flutter widget test.
//
// To perform an interaction with a widget in your test, use the WidgetTester
// utility that Flutter provides. For example, you can send tap and scroll
// gestures. You can also use WidgetTester to find child widgets in the widget
// tree, read text, and verify that the values of widget properties are correct.

import 'package:evo_client/model/data_point.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

import 'package:evo_client/main.dart';

void main() {
  test('Counter increments smoke test', () async {
    // Build our app and trigger a frame.
    var list = <int>[0, 0, 0, 0, 138, 166, 0, 0, 253, 223, 200, 66, 178, 51, 216, 65, 0, 0, 94, 188, 0, 0, 149, 189, 0, 224, 125, 63, 0, 128, 59, 62];

    var dp = DataPoint.create(list);
  });
}
