#include "FlightStateAnalyzer.h"
#include "Settings.h"
#include "Arduino.h"

FlightStateAnalyzer::FlightStateAnalyzer() {

}

void FlightStateAnalyzer::Init() {

}

void FlightStateAnalyzer::Loop(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN FlightStateAnalyzer::Loop()");
  if(state.SensorReadingsReady) {
    if(state.VehicleState == VehicleStateType::LaunchIdle && state.CurrentDataPoint.Acc_X > 1) {
      state.UpdateFlightState(VehicleStateType::Ascending);
    }
    else if(state.VehicleState == VehicleStateType::Ascending && state.CurrentDataPoint.KalmanAltitude < state.HeighestAltitude - 2) {
      state.UpdateFlightState(VehicleStateType::Descending);
    }
    else if(state.VehicleState == VehicleStateType::Descending && state.CurrentDataPoint.KalmanAltitude < state.Settings.LaunchAltitude + 5) {
      state.UpdateFlightState(VehicleStateType::Landed);
    }
  }
  if(DEBUG) Serial.println("END FlightStateAnalyzer::Loop()");
}