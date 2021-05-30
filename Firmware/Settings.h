#pragma once
#define DEBUG true

#define SOUND true
#define EXTERNAL_SOUND false
#define BUZZER_PIN 8
#define EXTERNAL_BUZZER_PIN 9

#define SD_CARD_PIN 5

#define SAVE_INTERVAL 50
#define BLE_UPDATE_INTERVAL 400


struct SettingsDto {
    float LaunchAltitude = 145.0f;
    float PressureNN = 1027.6f;
    char Name[16];
};
