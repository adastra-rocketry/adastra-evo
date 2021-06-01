#pragma once
#define DEBUG true
#define SOUND true
#define BUZZER_PIN 4
#define SAVE_INTERVAL 100
#define BLE_UPDATE_INTERVAL 400

#define GREEN_LED A2
#define YELLOW_LED A1
#define RED_LED A0

struct SettingsDto {
    float LaunchAltitude = 145.0f;
    float PressureNN = 1027.6f;
    char Name[16];
};
