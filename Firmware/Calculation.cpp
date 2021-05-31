#include "Calculation.h"
#include "SystemState.h"
#include "DataPoint.h"


Calculation::Calculation() {
  
}

void Calculation::Init() {

}

void Calculation::Loop(SystemState &state) {
  CalcPitchRollYaw(state.CurrentDataPoint);
}

void Calculation::CalcPitchRollYaw(DataPoint &dataPoint) {
  if(DEBUG) Serial.println("BEGIN Calculation::CalcPitchRollYaw()");

  if(DEBUG) Serial.println("END Calculation::CalcPitchRollYaw()");
}