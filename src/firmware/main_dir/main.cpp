#include <Arduino.h>
#include "../modules/network_module.cpp"
#include "../drivers/display_driver.cpp"
#include "../drivers/audio_driver.cpp"
#include "../modules/touch_module.cpp"
#include "../modules/power_module.cpp"
#include "../utils/logger.cpp"

NetworkModule networkModule;
DisplayDriver displayDriver;
AudioDriver audioDriver;
TouchModule touchModule;
PowerModule powerModule;

// Configuration
const char* WIFI_SSID = "Your_WiFi_SSID";
const char* WIFI_PASS = "Your_WiFi_Password";
const char* SERVER_ADDRESS = "192.168.1.100";
const int SERVER_PORT = 8000;

void setup() {
    // Initialize logger first for debugging
    Logger::init(LOG_DEBUG);
    Logger::info("MAIN", "System initialization starting...");
    
    // Initialize components
    if (!displayDriver.begin()) {
        Logger::error("MAIN", "Display initialization failed!");
    } else {
        Logger::info("MAIN", "Display initialized successfully");
    }
    
    if (!audioDriver.begin()) {
        Logger::error("MAIN", "Audio initialization failed!");
    } else {
        Logger::info("MAIN", "Audio initialized successfully");
    }
    
    if (!touchModule.begin()) {
        Logger::error("MAIN", "Touch sensor initialization failed!");
    } else {
        Logger::info("MAIN", "Touch sensor initialized successfully");
    }
    
    // Connect to WiFi
    Logger::info("MAIN", "Connecting to WiFi...");
    if (!networkModule.connect(WIFI_SSID, WIFI_PASS)) {
        Logger::error("MAIN", "Network connection failed!");
        displayDriver.showError("Network Error");
    } else {
        Logger::info("MAIN", "Connected to WiFi");
    }
    
    // Show ready status
    displayDriver.showStatus("System Ready");
    Logger::info("MAIN", "System initialization complete");
}

void loop() {
    static unsigned long lastLogTime = 0;
    
    // Main system loop
    networkModule.maintain();
    powerModule.checkStatus();
    
    // Handle touch events
    if (touchModule.checkTouch()) {
        Logger::debug("MAIN", "Touch event detected");
        handleTouchEvent(touchModule.getGesture());
    }
    
    // Handle audio input
    if (audioDriver.voiceDetected()) {
        Logger::info("MAIN", "Voice activity detected");
        handleVoiceCommand();
    }
    
    // Check battery status
    if (powerModule.needsAttention()) {
        Logger::warning("MAIN", "Battery level low");
        displayDriver.showBatteryWarning();
    }
    
    // Periodic status log
    if (millis() - lastLogTime > 30000) {  // Every 30 seconds
        lastLogTime = millis();
        Logger::info("MAIN", "System running, battery: " + String(powerModule.getBatteryLevel()) + "%");
    }
    
    delay(10); // Small delay to prevent watchdog issues
}

void handleTouchEvent(TouchGesture gesture) {
    switch (gesture) {
        case SINGLE_TAP:
            Logger::debug("TOUCH", "Single tap detected");
            displayDriver.toggleDisplay();
            break;
        case DOUBLE_TAP:
            Logger::debug("TOUCH", "Double tap detected");
            audioDriver.toggleMute();
            break;
        case LONG_PRESS:
            Logger::debug("TOUCH", "Long press detected");
            powerModule.togglePowerMode();
            break;
        default:
            Logger::warning("TOUCH", "Unknown gesture detected");
            break;
    }
}

void handleVoiceCommand() {
    Logger::info("AUDIO", "Processing voice command");
    String command = audioDriver.getVoiceCommand();
    Logger::debug("AUDIO", "Command text: " + command);
    
    Logger::info("NETWORK", "Sending command to server");
    String response = networkModule.sendCommand(command);
    Logger::debug("NETWORK", "Server response: " + response);
    
    audioDriver.playResponse(response);
    displayDriver.showText(response);
    Logger::info("AUDIO", "Voice command processed");
} 