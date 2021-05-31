#pragma once
#define DEBUG true
#define SOUND true
#define BUZZER_PIN 8
#define SAVE_INTERVAL 70
#define BLE_UPDATE_INTERVAL 400


struct SettingsDto {
    float LaunchAltitude = 145.0f;
    float PressureNN = 1027.6f;
    char Name[16];
};
