#include <Arduino.h>
#include <driver/i2s.h>
#include "../config/pinmap.h"

// I2S Configuration
#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 16000
#define SAMPLE_BITS 16
#define BUFFER_SIZE 512

// Variables
int16_t samples[BUFFER_SIZE];
int16_t audioLevel = 0;
unsigned long lastDisplayTime = 0;
const int displayInterval = 100; // Update interval in ms

// Status LED (onboard)
#define STATUS_LED 48

void setup() {
  // Initialize serial
  Serial.begin(115200);
  delay(1000);
  
  // Configure status LED
  pinMode(STATUS_LED, OUTPUT);
  
  // Blink LED to show initialization
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  
  Serial.println("\n\n");
  Serial.println("ESP32-S3 Microphone Test");
  Serial.println("========================");
  
  Serial.printf("Configuring I2S...\n");
  Serial.printf("- BCLK: GPIO%d\n", I2S_BCLK);
  Serial.printf("- LRCK: GPIO%d\n", I2S_LRCK);
  Serial.printf("- DIN: GPIO%d\n", I2S_DIN);
  
  // Configure I2S for microphone input
  esp_err_t err;
  
  // I2S configuration
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = (i2s_bits_per_sample_t)SAMPLE_BITS,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };
  
  // I2S pin configuration
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCK,
    .data_out_num = -1,  // Not using output
    .data_in_num = I2S_DIN
  };
  
  // Initialize I2S with configs
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed to install I2S driver: %d\n", err);
    return;
  }
  
  err = i2s_set_pin(I2S_PORT, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed to set I2S pins: %d\n", err);
    return;
  }
  
  Serial.println("I2S initialized successfully");
  Serial.println("Starting microphone test...");
  Serial.println("Speak into the microphone to see audio levels");
  Serial.println("LED will flash with audio input");
}

void loop() {
  // Read audio samples from I2S
  size_t bytes_read = 0;
  esp_err_t result = i2s_read(I2S_PORT, samples, sizeof(samples), &bytes_read, portMAX_DELAY);
  
  if (result == ESP_OK && bytes_read > 0) {
    // Process audio samples
    int samples_read = bytes_read / sizeof(int16_t);
    
    // Calculate audio level (simple peak detection)
    int16_t maxSample = 0;
    for (int i = 0; i < samples_read; i++) {
      int16_t sample = abs(samples[i]);
      if (sample > maxSample) {
        maxSample = sample;
      }
    }
    
    // Apply some smoothing
    audioLevel = (audioLevel * 3 + maxSample) / 4;
    
    // Normalize to 0-100 range for display
    int normalizedLevel = map(audioLevel, 0, 32768, 0, 100);
    
    // Display audio level periodically
    unsigned long currentTime = millis();
    if (currentTime - lastDisplayTime >= displayInterval) {
      lastDisplayTime = currentTime;
      
      // Print audio level bar
      Serial.print("[");
      for (int i = 0; i < 50; i++) {
        if (i < normalizedLevel / 2) {
          Serial.print("=");
        } else {
          Serial.print(" ");
        }
      }
      Serial.printf("] %d%%\r", normalizedLevel);
      
      // LED brightness based on audio level
      if (normalizedLevel > 10) {
        // Flash LED based on audio level
        digitalWrite(STATUS_LED, HIGH);
        delay(10);
        digitalWrite(STATUS_LED, LOW);
      }
    }
  }
} 