#include <Arduino.h>

// Status LED Test for ESP32-S3 board
// We've confirmed the onboard LED is on GPIO48 and is active LOW

#define STATUS_LED 48

void setup() {
    // Initialize serial
    Serial.begin(115200);
    delay(2000);
    
    Serial.println();
    Serial.println("================================");
    Serial.println("ESP32-S3 Status LED Test");
    Serial.println("================================");
    Serial.println("Blinking the onboard red LED on GPIO48");
    
    // Configure the status LED pin
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, HIGH);  // Start with LED off (active LOW)
}

void loop() {
    // Blink pattern 1: Simple toggle
    for (int i = 0; i < 5; i++) {
        Serial.println("LED ON");
        digitalWrite(STATUS_LED, LOW);   // Turn ON (active LOW)
        delay(500);
        Serial.println("LED OFF");
        digitalWrite(STATUS_LED, HIGH);  // Turn OFF (active LOW)
        delay(500);
    }
    
    // Blink pattern 2: Fast blinks
    Serial.println("Fast blink pattern");
    for (int i = 0; i < 10; i++) {
        digitalWrite(STATUS_LED, LOW);   // Turn ON
        delay(100);
        digitalWrite(STATUS_LED, HIGH);  // Turn OFF
        delay(100);
    }
    
    // Blink pattern 3: SOS (...---...)
    Serial.println("SOS pattern");
    
    // S (...)
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, LOW);
        delay(200);
        digitalWrite(STATUS_LED, HIGH);
        delay(200);
    }
    
    delay(300);
    
    // O (---)
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, LOW);
        delay(600);
        digitalWrite(STATUS_LED, HIGH);
        delay(200);
    }
    
    delay(300);
    
    // S (...)
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED, LOW);
        delay(200);
        digitalWrite(STATUS_LED, HIGH);
        delay(200);
    }
    
    // Pause between patterns
    delay(2000);
} 