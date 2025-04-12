#ifndef CONFIG_H
#define CONFIG_H

// System configuration
#define FIRMWARE_VERSION "0.0.1"
#define DEVICE_NAME "AI-Glasses"

// Network configuration
#define DEFAULT_WIFI_SSID "Your_WiFi_SSID"
#define DEFAULT_WIFI_PASS "Your_WiFi_Password"
#define DEFAULT_SERVER_URL "http://192.168.1.100:8000"
#define WIFI_CONNECT_TIMEOUT 20000
#define WIFI_RECONNECT_INTERVAL 5000

// Audio configuration
#define SAMPLE_RATE 16000
#define AUDIO_BUFFER_SIZE 1024
#define VOICE_THRESHOLD 1000.0
#define MIC_GAIN 20
#define AUDIO_TIMEOUT_MS 10000

// Power management
#define LOW_BATTERY_THRESHOLD 20.0
#define CRITICAL_BATTERY_THRESHOLD 10.0
#define BATTERY_CHECK_INTERVAL 30000
#define NORMAL_CPU_FREQ 240
#define ECO_CPU_FREQ 160
#define ULTRA_LOW_CPU_FREQ 80

// Display configuration
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_I2C_ADDR 0x3C
#define DISPLAY_ROTATION 0
#define DISPLAY_TIMEOUT 120000

// Debug configuration
#define DEBUG_ENABLED true
#define DEFAULT_LOG_LEVEL LOG_INFO

#endif
