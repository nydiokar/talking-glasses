#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../config/pinmap.h"
#include "../utils/logger.cpp"

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // No reset pin
#define OLED_ADDR 0x3C      // Common I2C address for SSD1306

class DisplayModule {
private:
    Adafruit_SSD1306* display;
    bool initialized;
    
public:
    DisplayModule() {
        display = nullptr;
        initialized = false;
    }
    
    ~DisplayModule() {
        if (display != nullptr) {
            delete display;
            display = nullptr;
        }
    }
    
    bool init() {
        Logger::info("Display", "Initializing OLED display");
        
        // Don't re-initialize if already done
        if (initialized) {
            return true;
        }
        
        // Create display instance
        display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        
        // Initialize the I2C bus first
        Wire.begin(OLED_SDA, OLED_SCL);
        
        Logger::debug("Display", "Starting display on I2C with SDA: " + 
                     String(OLED_SDA) + ", SCL: " + String(OLED_SCL));
        
        // Initialize the display
        if (!display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
            Logger::error("Display", "SSD1306 allocation failed");
            return false;
        }
        
        // Clear display & set defaults
        display->clearDisplay();
        display->setTextSize(1);
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(0, 0);
        
        // Show initialization message
        display->println("Smart Glasses");
        display->println("Initializing...");
        display->display();
        
        initialized = true;
        Logger::info("Display", "OLED display initialized successfully");
        return true;
    }
    
    void showText(const String& text, int x = 0, int y = 0) {
        if (!ensureInitialized()) return;
        
        display->clearDisplay();
        display->setCursor(x, y);
        display->println(text);
        display->display();
    }
    
    void showStatusScreen(const String& status, int batteryPercent) {
        if (!ensureInitialized()) return;
        
        display->clearDisplay();
        
        // Header
        display->setCursor(0, 0);
        display->println("Smart Glasses");
        display->println("-------------");
        
        // Status
        display->setCursor(0, 20);
        display->println(status);
        
        // Battery bar
        drawBatteryIndicator(0, 40, batteryPercent);
        
        display->display();
    }
    
    void showErrorScreen(const String& error) {
        if (!ensureInitialized()) return;
        
        display->clearDisplay();
        
        // Error header
        display->setCursor(0, 0);
        display->println("ERROR");
        display->println("-----");
        
        // Error message
        display->setCursor(0, 20);
        display->println(error);
        
        display->display();
    }
    
private:
    bool ensureInitialized() {
        if (!initialized) {
            return init();
        }
        return initialized;
    }
    
    void drawBatteryIndicator(int x, int y, int percent) {
        // Battery outline
        display->drawRect(x, y, 100, 10, SSD1306_WHITE);
        display->drawRect(x + 100, y + 2, 4, 6, SSD1306_WHITE);
        
        // Fill based on percentage
        int fillWidth = map(percent, 0, 100, 0, 98);
        display->fillRect(x + 1, y + 1, fillWidth, 8, SSD1306_WHITE);
        
        // Show percentage text
        display->setCursor(x + 40, y + 20);
        display->print(percent);
        display->print("%");
    }
}; 