#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin definitions
#define OLED_SDA 17
#define OLED_SCL 18
#define STATUS_LED 48

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // No reset pin
#define OLED_ADDR 0x3C      // Common I2C address for SSD1306

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Counter for animation
int counter = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);
  
  // Set up status LED
  pinMode(STATUS_LED, OUTPUT);
  
  // Blink LED to show we're starting
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  
  Serial.println("\n\n");
  Serial.println("ESP32-S3 OLED Display Test");
  Serial.println("==========================");
  
  // Initialize I2C
  Wire.begin(OLED_SDA, OLED_SCL);
  
  Serial.printf("Initializing OLED on pins SDA:%d, SCL:%d\n", OLED_SDA, OLED_SCL);
  
  // Initialize OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    // Rapid blink to show error
    while (true) {
      digitalWrite(STATUS_LED, HIGH);
      delay(100);
      digitalWrite(STATUS_LED, LOW);
      delay(100);
    }
  }
  
  Serial.println("OLED initialized successfully!");
  
  // Clear the display buffer
  display.clearDisplay();
  
  // Set text properties
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Show welcome message
  display.setCursor(0, 0);
  display.println("OLED Test Successful!");
  display.println("");
  display.println("Display Info:");
  display.printf("- SDA: GPIO%d\n", OLED_SDA);
  display.printf("- SCL: GPIO%d\n", OLED_SCL);
  display.printf("- Addr: 0x%02X\n", OLED_ADDR);
  display.display();
  
  // Wait for user to read message
  delay(3000);
}

void drawProgressBar(int x, int y, int width, int height, int progress) {
  // Draw outline
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  
  // Calculate width of filled portion
  int fillWidth = (width - 2) * progress / 100;
  
  // Fill progress bar
  display.fillRect(x + 1, y + 1, fillWidth, height - 2, SSD1306_WHITE);
}

void loop() {
  // Clear display for new frame
  display.clearDisplay();
  
  // Draw header
  display.setCursor(0, 0);
  display.println("Smart Glasses");
  display.println("-------------");
  
  // Update counter (0-100)
  counter = (counter + 1) % 101;
  
  // Draw animated progress bar
  drawProgressBar(10, 20, 108, 10, counter);
  
  // Show percentage
  display.setCursor(55, 35);
  display.printf("%d%%", counter);
  
  // Draw some graphics at the bottom
  for (int i = 0; i < 6; i++) {
    int x = i * 22 + 4;
    int height = 10 + ((counter + i * 10) % 20);
    display.fillRect(x, 64 - height, 12, height, SSD1306_WHITE);
  }
  
  // Send to display
  display.display();
  
  // Blink LED occasionally
  if (counter % 25 == 0) {
    digitalWrite(STATUS_LED, HIGH);
    delay(50);
    digitalWrite(STATUS_LED, LOW);
  }
  
  // Small delay 
  delay(50);
} 