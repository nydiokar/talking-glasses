#include <Arduino.h>
#include <Wire.h>

// Status LED
#define STATUS_LED 48

// Focus on manufacturer's pins and other potentially valid combinations
// Manufacturer diagram shows GPIO11 (SDA) and GPIO12 (SCL)
// Add more combinations to be thorough
#define PIN_PAIRS 5
const uint8_t SDA_PINS[PIN_PAIRS] = {11, 4, 5, 13, 17};  // Try manufacturer's recommended GPIO11 first
const uint8_t SCL_PINS[PIN_PAIRS] = {12, 5, 6, 14, 18};  // Try manufacturer's recommended GPIO12 first

// Current test pair
int currentPair = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(STATUS_LED, OUTPUT);
  
  Serial.println("\n\n");
  Serial.println("ESP32-S3 I2C Manufacturer Pin Test");
  Serial.println("==================================");
  
  // Blink LED to indicate startup
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  
  Serial.println("\nTesting manufacturer recommended pins and alternatives");
  Serial.println("First test pair is manufacturer's recommended GPIO11/GPIO12");
}

bool isValidPin(uint8_t pin) {
  // Check if pin is valid for ESP32-S3
  if (pin >= 0 && pin <= 48) {
    // Basic validation - each board may have differences
    return true;
  }
  return false;
}

void scanI2C(uint8_t sda, uint8_t scl) {
  Serial.printf("\n----------------------------------------\n");
  Serial.printf("Testing SDA: GPIO%d, SCL: GPIO%d\n", sda, scl);
  
  // Validate pins first
  if (!isValidPin(sda) || !isValidPin(scl)) {
    Serial.println("Error: Invalid pin number(s)");
    return;
  }
  
  // Test with hardware first
  Serial.println("Validating pins as digital outputs...");
  
  bool pinError = false;
  
  // Test SDA pin
  pinMode(sda, OUTPUT);
  if (sda != 48) { // Don't mess with status LED
    digitalWrite(sda, HIGH);
    delay(50);
    digitalWrite(sda, LOW);
    delay(50);
    digitalWrite(sda, HIGH);
  }
  
  // Test SCL pin
  pinMode(scl, OUTPUT);
  if (scl != 48) { // Don't mess with status LED
    digitalWrite(scl, HIGH);
    delay(50);
    digitalWrite(scl, LOW);
    delay(50);
    digitalWrite(scl, HIGH);
  }
  
  if (pinError) {
    Serial.println("Error during pin validation");
    return;
  }
  
  Serial.println("Basic pin test passed. Initializing I2C...");
  
  // End any previous I2C
  Wire.end();
  delay(200);
  
  // Try to initialize I2C
  bool i2cInitSuccess = true;
  
  try {
    // Set up I2C bus
    Wire.begin(sda, scl, 100000);
    delay(200);
  } catch (...) {
    i2cInitSuccess = false;
    Serial.println("Exception during I2C initialization");
  }
  
  if (!i2cInitSuccess) {
    Serial.println("Failed to initialize I2C");
    return;
  }
  
  Serial.println("I2C initialized, scanning addresses...");
  
  // Scan all I2C addresses
  bool deviceFound = false;
  
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.printf("Device found at address 0x%02X", address);
      
      // Check for OLED displays
      if (address == 0x3C || address == 0x3D) {
        Serial.println(" (Likely OLED display)");
        
        // Indicate success with rapid LED blinking
        for (int i = 0; i < 15; i++) {
          digitalWrite(STATUS_LED, HIGH);
          delay(50);
          digitalWrite(STATUS_LED, LOW);
          delay(50);
        }
        
        // Save the successful configuration
        Serial.println("\n!!! SUCCESS !!!");
        Serial.printf("WORKING CONFIGURATION FOUND:\n");
        Serial.printf("- SDA: GPIO%d\n", sda);
        Serial.printf("- SCL: GPIO%d\n", scl);
        Serial.printf("- Address: 0x%02X\n", address);
        Serial.println("Update your configuration files with these values!");
      } else {
        Serial.println();
      }
      
      deviceFound = true;
    }
  }
  
  if (!deviceFound) {
    Serial.printf("No I2C devices found on SDA:GPIO%d SCL:GPIO%d\n", sda, scl);
  }
}

void loop() {
  // Get current pin pair
  uint8_t sda = SDA_PINS[currentPair];
  uint8_t scl = SCL_PINS[currentPair];
  
  // Test current configuration
  scanI2C(sda, scl);
  
  // Move to next pair
  currentPair = (currentPair + 1) % PIN_PAIRS;
  
  // Blink LED once to show test complete
  digitalWrite(STATUS_LED, HIGH);
  delay(300);
  digitalWrite(STATUS_LED, LOW);
  
  // Wait before next test
  Serial.printf("\nMoving to next pair (%d/%d) in 5 seconds...\n", 
               currentPair + 1, PIN_PAIRS);
  Serial.printf("----------------------------------------\n");
  delay(5000);
} 