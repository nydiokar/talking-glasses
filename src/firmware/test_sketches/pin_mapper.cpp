#include <Arduino.h>

// Status LED
#define STATUS_LED 48

// Pins to test
#define NUM_PINS 21
const int pinsToTest[NUM_PINS] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
  11, 12, 13, 14, 15, 16, 17, 18, 19, 20
};

// Current pin being tested
int currentPinIndex = 0;
unsigned long lastSwitchTime = 0;
const unsigned long PIN_TEST_DURATION = 5000; // 5 seconds per pin

void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(1000);
  
  // Configure the LED
  pinMode(STATUS_LED, OUTPUT);
  
  // Blink LED to show initialization
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  
  Serial.println("\n\n");
  Serial.println("ESP32-S3 Physical Pin to GPIO Mapper");
  Serial.println("===================================");
  Serial.println("Instructions:");
  Serial.println("1. Connect a jumper wire from GND to the pin being tested");
  Serial.println("2. The LED will light up when the connection is made");
  Serial.println("3. This confirms the physical pin corresponds to the GPIO number");
  Serial.println("4. We'll test one pin at a time");

  // Start with the first pin
  setupCurrentPin();
}

void setupCurrentPin() {
  int pin = pinsToTest[currentPinIndex];
  
  // Configure the current pin as INPUT_PULLUP
  // This will make it HIGH normally, and LOW when connected to GND
  pinMode(pin, INPUT_PULLUP);
  
  // Show which pin we're testing
  Serial.printf("\n>>> Now testing GPIO%d <<<\n", pin);
  Serial.println("Connect this GPIO to GND to confirm pin mapping");
  Serial.printf("Testing for %d seconds...\n", PIN_TEST_DURATION/1000);
  
  // Reset timer
  lastSwitchTime = millis();
}

void loop() {
  // Get current pin
  int currentPin = pinsToTest[currentPinIndex];
  
  // Read the pin state
  int pinState = digitalRead(currentPin);
  
  // If pin is connected to GND (LOW), turn on LED
  digitalWrite(STATUS_LED, !pinState);  // Invert because LOW means connected
  
  // Display pin state
  Serial.printf("GPIO%d: %s       \r", currentPin, 
               (pinState == LOW) ? "CONNECTED TO GND ✓" : "Not connected");
  
  // Check if it's time to switch to next pin
  unsigned long currentTime = millis();
  if (currentTime - lastSwitchTime >= PIN_TEST_DURATION) {
    // Switch to next pin
    currentPinIndex = (currentPinIndex + 1) % NUM_PINS;
    
    // Blink LED to show pin change
    for (int i = 0; i < 3; i++) {
      digitalWrite(STATUS_LED, HIGH);
      delay(50);
      digitalWrite(STATUS_LED, LOW);
      delay(50);
    }
    
    // Setup the new pin
    setupCurrentPin();
  }
  
  // Small delay
  delay(100);
} 