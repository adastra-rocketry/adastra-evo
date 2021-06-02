#pragma once
#include "..\SystemState\VehicleStateType.h"

#define DEBUG false
#define SOUND true
#define BUZZER_PIN 4
#define SAVE_INTERVAL 50
#define BLE_UPDATE_INTERVAL 400

#define PYRO_1_PIN 2
#define PYRO_2_PIN 3
#define PYRO_1_CONTINUITY_PIN 6
#define PYRO_2_CONTINUITY_PIN 7

#define GREEN_LED A2
#define YELLOW_LED A1
#define RED_LED A0

#define BUTTON_PIN 5

struct SettingsDto {
    float LaunchAltitude = 145.0f;
    float PressureNN = 1027.6f;
    char Name[16];

    VehicleStateType Pyro1ActionState;
    VehicleStateType Pyro2ActionState;
};
