/*
  RunCam.h
*/
#pragma once
#include "SystemState/SystemState.h"
#include "Arduino.h"
#include "SystemState/SystemState.h"

enum class RunCamCommand {
  RCDEVICE_PROTOCOL_COMMAND_GET_DEVICE_INFO = 0x00,
  RCDEVICE_PROTOCOL_COMMAND_CAMERA_CONTROL = 0x01,
  RCDEVICE_PROTOCOL_COMMAND_5KEY_SIMULATION_PRESS = 0x02,
  RCDEVICE_PROTOCOL_COMMAND_5KEY_SIMULATION_RELEASE = 0x03,
  RCDEVICE_PROTOCOL_COMMAND_5KEY_CONNECTION = 0x04,
  COMMAND_NONE
};

enum class ControlOperation {
    RCDEVICE_PROTOCOL_SIMULATE_WIFI_BTN = 0x00, // WiFi/Mode button
    RCDEVICE_PROTOCOL_SIMULATE_POWER_BTN = 0x01,
    RCDEVICE_PROTOCOL_CHANGE_MODE = 0x02,
    RCDEVICE_PROTOCOL_CHANGE_START_RECORDING = 0x03,
    RCDEVICE_PROTOCOL_CHANGE_STOP_RECORDING = 0x04,
    UNKNOWN_CAMERA_OPERATION = 0xFF
};


class RunCam
{
  public:
    RunCam(SystemState &state);
    void Init();
    void Loop();
  private:
    SystemState &State;
    void StartRecording();
    void StopRecording();
    bool IsRecording = false;
    void SendPacket(RunCamCommand command, uint8_t param);
    uint8_t Crc8DvbS2(uint8_t crc, unsigned char a);
    void GetDeviceInfo();
};