#include <Arduino.h>

void setup() {
    // Initialize serial with a delay for USB CDC
    Serial.begin(115200);
    delay(3000);  // Longer delay to ensure USB CDC is ready
    
    // Debug LED blink to show the board is running regardless of serial
    pinMode(2, OUTPUT);
    for (int i = 0; i < 5; i++) {
        digitalWrite(2, HIGH);
        delay(200);
        digitalWrite(2, LOW);
        delay(200);
    }
    
    Serial.println("\n\n\n");
    Serial.println("================================");
    Serial.println("ESP32-S3 Basic Serial Test");
    Serial.println("================================");
}

void loop() {
    Serial.println("Hello from ESP32-S3! If you can see this, serial is working.");
    
    // Blink onboard LED to indicate the device is running
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
} 