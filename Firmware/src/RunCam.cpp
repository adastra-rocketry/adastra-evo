#include "RunCam.h"

RunCam::RunCam(SystemState &state) : State{ state } {
  
}

void RunCam::Init() {
  if(DEBUG) Serial.println("BEGIN RunCam::Init()");
  Serial1.begin(9600);
  Serial.println("Connecting to RunCam");
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  Serial.println("Done");
  if(DEBUG) Serial.println("END RunCam::Init()");
}

void RunCam::Loop() {
  if(DEBUG) Serial.println("BEGIN RunCam::Loop()");
  switch (State.VehicleState)
  {
  case VehicleStateType::Idle:
    break;
  case VehicleStateType::LaunchIdle:
  case VehicleStateType::Ascending:
  case VehicleStateType::Descending:
    if(!IsRecording) {
      StartRecording();
    }
    break;
  case VehicleStateType::Landed:
    if(IsRecording) {
      StopRecording();
    }
    break;

  case VehicleStateType::Calibrating:
  case VehicleStateType::Error:
  default:
    break;
  }
  if(DEBUG) Serial.println("END RunCam::Loop()");
}

void RunCam::StartRecording() {
  Serial.println("BEGIN RunCam::StartRecording()");
  SendPacket(RunCamCommand::RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL, uint8_t(ControlOperation::RCDEVICE_PROTOCOL_SIMULATE_POWER_BTN));
  IsRecording = true;
  Serial.println("END RunCam::StartRecording()");
}

void RunCam::StopRecording() {
  SendPacket(RunCamCommand::RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL, uint8_t(ControlOperation::RCDEVICE_PROTOCOL_SIMULATE_POWER_BTN));
  IsRecording = false;
}

void RunCam::SendPacket(RunCamCommand command, uint8_t param) {
  if(DEBUG) Serial.println("BEGIN RunCam::SendPacket()");
  uint8_t buffer[4];
  buffer[0] = 0xCC;
  buffer[1] = uint8_t(command);

  bool have_param = param > 0 || command == RunCamCommand::RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL;
  uint8_t buffer_len = have_param ? 4 : 3;
  if (have_param) {
    buffer[2] = param;
  }
  
  uint8_t crc = 0;
  for (uint8_t i = 0; i < buffer_len - 1; i++) {
      crc = Crc8DvbS2(crc, buffer[i]);
  }
  buffer[buffer_len - 1] = crc;

  Serial1.write(buffer, buffer_len);
  Serial1.flush();
  if(DEBUG) Serial.println("END RunCam::SendPacket()");
}

void RunCam::GetDeviceInfo() {
  
}

uint8_t RunCam::Crc8DvbS2(uint8_t crc, unsigned char a)
{
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }

    return crc;
}