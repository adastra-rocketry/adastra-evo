#include "FlightStateAnalyzer.h"

FlightStateAnalyzer::FlightStateAnalyzer() {

}

void FlightStateAnalyzer::Init() {

}

void FlightStateAnalyzer::Loop(SystemState &state) {
  if(state.VehicleState == VehicleStateType::LaunchIdle && state.CurrentDataPoint.Acc_X > 1) {
    state.VehicleState = VehicleStateType::Ascending;
  }
  else if(state.VehicleState == VehicleStateType::Ascending && state.CurrentDataPoint.KalmanAltitude < state.HeighestAltitude - 2) {
    state.VehicleState = VehicleStateType::Descending;
  }
  else if(state.VehicleState == VehicleStateType::Descending && state.CurrentDataPoint.KalmanAltitude < state.LaunchAltitude + 5) {
    state.VehicleState = VehicleStateType::Landed;
  }
}