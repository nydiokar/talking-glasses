#include <Arduino.h>
#include "network_manager.h"
#include "display_manager.h"
#include "audio_manager.h"
#include "touch_manager.h"
#include "power_manager.h"

NetworkManager networkManager;
DisplayManager displayManager;
AudioManager audioManager;
TouchManager touchManager;
PowerManager powerManager;

// Configuration
const char* WIFI_SSID = "Your_WiFi_SSID";
const char* WIFI_PASS = "Your_WiFi_Password";
const char* SERVER_ADDRESS = "192.168.1.100";
const int SERVER_PORT = 8000;

void setup() {
    Serial.begin(115200);
    
    // Initialize components
    if (!displayManager.begin()) {
        Serial.println("Display initialization failed!");
    }
    
    if (!audioManager.begin()) {
        Serial.println("Audio initialization failed!");
    }
    
    if (!touchManager.begin()) {
        Serial.println("Touch sensor initialization failed!");
    }
    
    // Connect to WiFi
    if (!networkManager.connect(WIFI_SSID, WIFI_PASS)) {
        Serial.println("Network connection failed!");
        displayManager.showError("Network Error");
    }
    
    // Show ready status
    displayManager.showStatus("System Ready");
}

void loop() {
    // Main system loop
    networkManager.maintain();
    powerManager.checkStatus();
    
    // Handle touch events
    if (touchManager.checkTouch()) {
        handleTouchEvent(touchManager.getGesture());
    }
    
    // Handle audio input
    if (audioManager.voiceDetected()) {
        handleVoiceCommand();
    }
    
    // Check battery status
    if (powerManager.needsAttention()) {
        displayManager.showBatteryWarning();
    }
    
    delay(10); // Small delay to prevent watchdog issues
}

void handleTouchEvent(TouchGesture gesture) {
    switch (gesture) {
        case SINGLE_TAP:
            displayManager.toggleDisplay();
            break;
        case DOUBLE_TAP:
            audioManager.toggleMute();
            break;
        case LONG_PRESS:
            powerManager.togglePowerMode();
            break;
    }
}

void handleVoiceCommand() {
    String command = audioManager.getVoiceCommand();
    String response = networkManager.sendCommand(command);
    audioManager.playResponse(response);
    displayManager.showText(response);
}