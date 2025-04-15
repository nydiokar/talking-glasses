#include <Arduino.h>

// Define pins
#define TOUCH_PIN 8      // D5 is GPIO8
#define STATUS_LED 48    // Onboard LED
#define DISPLAY_INTERVAL 100  // ms

// Touch detection variables - note this detects INCREASES rather than decreases
#define TOUCH_THRESHOLD 25000  // Value must increase above this from baseline
#define BASELINE_SAMPLES 50    // Number of samples to establish baseline

// Variables 
int touchValue = 0;
int baselineValue = 0;
bool touchDetected = false;
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
  Serial.println("ESP32-S3 D5/GPIO8 Touch Sensor Test");
  Serial.println("==================================");
  Serial.println("This pin INCREASES value when touched (opposite behavior)");
  
  // Establish baseline reading (average of multiple samples)
  Serial.println("Establishing baseline (don't touch the sensor)...");
  long total = 0;
  for (int i = 0; i < BASELINE_SAMPLES; i++) {
    total += touchRead(TOUCH_PIN);
    delay(10);
  }
  baselineValue = total / BASELINE_SAMPLES;
  
  Serial.printf("Baseline established: %d\n", baselineValue);
  Serial.printf("Touch threshold: >%d\n", TOUCH_THRESHOLD);
  Serial.println("Touch the sensor (D5/GPIO8) to see changes");
}

void loop() {
  // Read touch value
  touchValue = touchRead(TOUCH_PIN);
  
  // Detect touch based on threshold ABOVE baseline
  // This is opposite of normal touch sensors
  touchDetected = (touchValue > TOUCH_THRESHOLD);
  
  // Control LED based on touch
  digitalWrite(STATUS_LED, touchDetected ? HIGH : LOW);
  
  // Display touch value periodically
  unsigned long currentTime = millis();
  if (currentTime - lastDisplayTime >= DISPLAY_INTERVAL) {
    lastDisplayTime = currentTime;
    
    // Calculate touch delta from baseline
    int touchDelta = touchValue - baselineValue;
    
    // Display touch value and bar graph
    Serial.print("[");
    
    // Bar length based on delta (inverted)
    int barLength = map(constrain(touchDelta, 0, 50000), 0, 50000, 0, 50);
    
    for (int i = 0; i < 50; i++) {
      if (i < barLength) {
        Serial.print("=");
      } else {
        Serial.print(" ");
      }
    }
    
    // Print status
    if (touchDetected) {
      Serial.printf("] %d (delta: +%d) TOUCH DETECTED\r", touchValue, touchDelta);
    } else {
      Serial.printf("] %d (delta: %d)          \r", touchValue, touchDelta);
    }
  }
  
  // Small delay
  delay(10);
} 