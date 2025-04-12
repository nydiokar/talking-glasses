#include <Arduino.h>
#include <Wire.h>

// Pin definitions for ESP32-S3
// Using ESP32-S3 standard I2C pins
#define SDA_PIN 8  // Changed from 21 to 8
#define SCL_PIN 9  // Changed from 22 to 9 
#define STATUS_LED 2

void setup() {
    // Initialize serial
    Serial.begin(115200);
    delay(2000);
    
    Serial.println();
    Serial.println("================================");
    Serial.println("ESP32-S3-Nano I2C Test");
    Serial.println("================================");
    
    // Configure status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, LOW);  // Start with LED off
    
    // Initialize I2C
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.printf("I2C initialized on pins SDA: %d, SCL: %d\n", SDA_PIN, SCL_PIN);
    
    // Blink LED to show initialization complete
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, HIGH);
        delay(100);
        digitalWrite(STATUS_LED, LOW);
        delay(100);
    }
}

void loop() {
    Serial.println("\nScanning I2C bus...");
    
    byte deviceCount = 0;
    
    // Scan addresses 1-127
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        
        if (error == 0) {
            Serial.printf("Device found at address 0x%02X", address);
            
            // Additional info for known devices
            switch (address) {
                case 0x3C:
                case 0x3D:
                    Serial.println(" (Likely OLED display)");
                    break;
                case 0x68:
                    Serial.println(" (Likely MPU6050)");
                    break;
                default:
                    Serial.println();
            }
            
            deviceCount++;
        }
    }
    
    if (deviceCount == 0) {
        Serial.println("No I2C devices found");
    } else {
        Serial.printf("Found %d I2C device(s)\n", deviceCount);
    }
    
    // Blink LED to show scan completed
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    
    Serial.println("Waiting 5 seconds before next scan...");
    Serial.println("================================");
    delay(5000);
} 