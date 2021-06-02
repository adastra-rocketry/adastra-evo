#include "PyroChannels.h"

// Remember - the Pyrochannels and their continuity check don't work when powered from USB

PyroChannels::PyroChannels(SystemState &state) : State{ state }
{
}

void PyroChannels::Init()
{
  pinMode(PYRO_1_CONTINUITY_PIN, INPUT);
  pinMode(PYRO_2_CONTINUITY_PIN, INPUT);
  pinMode(PYRO_1_PIN, OUTPUT);
  pinMode(PYRO_2_PIN, OUTPUT);
  digitalWrite(PYRO_1_PIN, LOW);
  digitalWrite(PYRO_2_PIN, LOW);
}

void PyroChannels::Loop()
{
  switch (State.VehicleState)
  {
    case VehicleStateType::Idle:
      CheckContinuity();
      break;
    case VehicleStateType::LaunchIdle:
    case VehicleStateType::Ascending:
    case VehicleStateType::Descending:
    case VehicleStateType::Landed:
    case VehicleStateType::Calibrating:
    case VehicleStateType::Error:
    default:
      break;
  }
}

void PyroChannels::CheckContinuity()
{
  int buttonState = digitalRead(PYRO_1_CONTINUITY_PIN);
  State.PyroChannel.PyroChannel1Continuity = (buttonState == HIGH);

  buttonState = digitalRead(PYRO_2_CONTINUITY_PIN);
  State.PyroChannel.PyroChannel2Continuity = (buttonState == HIGH);
}