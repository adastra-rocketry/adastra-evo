#include "FlightStateAnalyzer.h"

FlightStateAnalyzer::FlightStateAnalyzer(SystemState &State) : State{ State } {

}

void FlightStateAnalyzer::Init() {

}

void FlightStateAnalyzer::Loop() {
  if(DEBUG) Serial.println("BEGIN FlightStateAnalyzer::Loop()");
  if(State.VehicleState == VehicleStateType::LaunchIdle && State.CurrentDataPoint.Acc_X > 1) {
    State.UpdateFlightState(VehicleStateType::Ascending);
  }
  else if(State.VehicleState == VehicleStateType::Ascending && State.CurrentDataPoint.KalmanAltitude < State.HeighestAltitude - 2) {
    State.UpdateFlightState(VehicleStateType::Descending);
  }
  else if(State.VehicleState == VehicleStateType::Descending && State.CurrentDataPoint.KalmanAltitude < State.Settings.LaunchAltitude + 5) {
    State.UpdateFlightState(VehicleStateType::Landed);
  }
  if(DEBUG) Serial.println("END FlightStateAnalyzer::Loop()");
}