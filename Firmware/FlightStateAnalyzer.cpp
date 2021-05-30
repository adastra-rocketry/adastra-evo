#include "FlightStateAnalyzer.h"
#include "Settings.h"
#include "Arduino.h"

FlightStateAnalyzer::FlightStateAnalyzer() {

}

void FlightStateAnalyzer::Init() {

}

void FlightStateAnalyzer::Loop(SystemState &state) {
  if(DEBUG) Serial.println("BEGIN FlightStateAnalyzer::Loop()");
  if(state.VehicleState == VehicleStateType::LaunchIdle && state.CurrentDataPoint.Acc_X > 1) {
    state.VehicleState = VehicleStateType::Ascending;
    
    tone(BUZZER_PIN, 800, 100);
  }
  else if(state.VehicleState == VehicleStateType::Ascending && state.CurrentDataPoint.KalmanAltitude < state.HeighestAltitude - 2) {
    state.VehicleState = VehicleStateType::Descending;
    tone(BUZZER_PIN, 800, 100);
  }
  else if(state.VehicleState == VehicleStateType::Descending && state.CurrentDataPoint.KalmanAltitude < state.Settings.LaunchAltitude + 5) {
    state.VehicleState = VehicleStateType::Landed;
    tone(BUZZER_PIN, 800, 100);
  }
  if(DEBUG) Serial.println("END FlightStateAnalyzer::Loop()");
}