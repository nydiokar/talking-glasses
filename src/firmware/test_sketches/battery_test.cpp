#include <Arduino.h>
#include "../config/pinmap.h"

// Configuration
#define STATUS_LED 48
#define DISPLAY_INTERVAL 1000  // Update every second
#define BATTERY_SAMPLES 10     // Average multiple readings
#define VOLTAGE_MULTIPLIER 2.0 // Voltage divider ratio (adjust based on your hardware)
#define FULL_BATTERY_VOLTAGE 4.2
#define EMPTY_BATTERY_VOLTAGE 3.3

// Variables
float battery1Voltage = 0.0;
float battery2Voltage = 0.0;
unsigned long lastDisplayTime = 0;

void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(1000);
  
  // Initialize LED
  pinMode(STATUS_LED, OUTPUT);
  
  // Blink LED to show initialization
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  
  Serial.println("\n\n");
  Serial.println("ESP32-S3 Battery Monitor Test");
  Serial.println("============================");
  Serial.printf("Battery 1 monitoring on GPIO%d\n", BAT1_VOLTAGE_PIN);
  Serial.printf("Battery 2 monitoring on GPIO%d\n", BAT2_VOLTAGE_PIN);
  
  // Note: ESP32-S3 uses 0-3.3V analog range with 12-bit resolution (0-4095)
  // Configure ADC
  analogReadResolution(12); // 12-bit resolution
}

// Reads battery voltage with averaging
float readBatteryVoltage(int pin) {
  // Read multiple samples and average
  int total = 0;
  for (int i = 0; i < BATTERY_SAMPLES; i++) {
    total += analogRead(pin);
    delay(5);
  }
  int average = total / BATTERY_SAMPLES;
  
  // Convert to voltage
  // ADC value to voltage: (ADC / 4095) * 3.3V * MULTIPLIER
  float voltage = (average / 4095.0) * 3.3 * VOLTAGE_MULTIPLIER;
  
  return voltage;
}

// Calculate battery percentage
int calculateBatteryPercentage(float voltage) {
  // Simple linear mapping from voltage to percentage
  int percentage = map(voltage * 100, 
                       EMPTY_BATTERY_VOLTAGE * 100, 
                       FULL_BATTERY_VOLTAGE * 100, 
                       0, 100);
  return constrain(percentage, 0, 100);
}

// Display a horizontal bar
void displayBar(int percentage, char symbol) {
  // Bar length based on percentage (0-50 chars)
  int barLength = map(percentage, 0, 100, 0, 50);
  
  Serial.print("[");
  for (int i = 0; i < 50; i++) {
    if (i < barLength) {
      Serial.print(symbol);
    } else {
      Serial.print(" ");
    }
  }
  Serial.print("]");
}

void loop() {
  // Read battery voltages
  battery1Voltage = readBatteryVoltage(BAT1_VOLTAGE_PIN);
  battery2Voltage = readBatteryVoltage(BAT2_VOLTAGE_PIN);
  
  // Calculate battery percentages
  int battery1Percentage = calculateBatteryPercentage(battery1Voltage);
  int battery2Percentage = calculateBatteryPercentage(battery2Voltage);
  
  // Display battery info periodically
  unsigned long currentTime = millis();
  if (currentTime - lastDisplayTime >= DISPLAY_INTERVAL) {
    lastDisplayTime = currentTime;
    
    // Battery 1 info
    Serial.printf("\nBattery 1: %.2fV (%d%%)\n", battery1Voltage, battery1Percentage);
    displayBar(battery1Percentage, '#');
    Serial.println();
    
    // Battery 2 info
    Serial.printf("Battery 2: %.2fV (%d%%)\n", battery2Voltage, battery2Percentage);
    displayBar(battery2Percentage, '#');
    Serial.println();
    
    // Overall status
    float averageVoltage = (battery1Voltage + battery2Voltage) / 2.0;
    int averagePercentage = (battery1Percentage + battery2Percentage) / 2;
    
    Serial.printf("Combined: %.2fV (%d%%)\n", averageVoltage, averagePercentage);
    
    // Flash LED when batteries are low
    if (averagePercentage < 20) {
      digitalWrite(STATUS_LED, HIGH);
      delay(50);
      digitalWrite(STATUS_LED, LOW);
    }
  }
  
  // Small delay
  delay(10);
} 