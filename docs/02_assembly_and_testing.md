# Assembly and Testing Procedures

## Phase 1: Initial Component Testing

### 1. Basic ESP32-S3 Setup
```cpp
// Test code for ESP32-S3 basic functionality
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("ESP32-S3 Basic Test");
}

void loop() {
    Serial.println("System running...");
    delay(1000);
}
```

### 2. OLED Display Testing
```cpp
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        return;
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(F("OLED Test"));
    display.display();
}
```

### 3. Touch Sensor Setup
```cpp
#define TOUCH_PIN 4

void setup() {
    Serial.begin(115200);
    pinMode(TOUCH_PIN, INPUT);
}

void loop() {
    if(digitalRead(TOUCH_PIN) == HIGH) {
        Serial.println("Touch detected!");
        delay(200);  // Debounce
    }
}
```

### 4. Microphone Testing
```cpp
#define MIC_PIN 36

void setup() {
    Serial.begin(115200);
    pinMode(MIC_PIN, INPUT);
}

void loop() {
    int micValue = analogRead(MIC_PIN);
    Serial.println(micValue);
    delay(100);
}
```

## Phase 2: Component Integration

### 1. Power Distribution Setup
```cpp
// Battery monitoring
#define BAT1_PIN 35
#define BAT2_PIN 34

float getBatteryVoltage(int pin) {
    float reading = analogRead(pin);
    return (reading / 4095.0) * 3.3 * 2; // Voltage divider ratio
}
```

### 2. Full System Test
```cpp
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define TOUCH_PIN 4
#define MIC_PIN 36
#define BAT1_PIN 35
#define BAT2_PIN 34

// OLED Setup
Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
    Serial.begin(115200);
    
    // Initialize display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Display failed"));
        return;
    }
    
    // Initialize touch
    pinMode(TOUCH_PIN, INPUT);
    
    // Initialize mic
    pinMode(MIC_PIN, INPUT);
    
    showStatus("System Ready");
}

void showStatus(String message) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(message);
    display.display();
}

void loop() {
    // Monitor touch
    if(digitalRead(TOUCH_PIN) == HIGH) {
        showStatus("Touch detected");
        delay(200);
    }
    
    // Monitor battery
    float bat1 = getBatteryVoltage(BAT1_PIN);
    float bat2 = getBatteryVoltage(BAT2_PIN);
    
    // Show battery status every 30 seconds
    static unsigned long lastBatCheck = 0;
    if(millis() - lastBatCheck > 30000) {
        showStatus("Bat1: " + String(bat1) + "V\nBat2: " + String(bat2) + "V");
        lastBatCheck = millis();
    }
}
```

## Testing Procedures

### 1. Power System Testing
- [ ] Test each battery individually
- [ ] Verify protection circuit functionality
- [ ] Test voltage regulation
- [ ] Measure power consumption in different states
- [ ] Test battery switching mechanism

### 2. Display Testing
- [ ] Test in different lighting conditions
- [ ] Verify viewing angles
- [ ] Check refresh rate
- [ ] Test power consumption
- [ ] Verify I2C communication reliability

### 3. Touch Interface Testing
- [ ] Test touch sensitivity
- [ ] Verify debounce functionality
- [ ] Test in different environmental conditions
- [ ] Measure response time
- [ ] Verify gesture recognition

### 4. Audio System Testing
- [ ] Test microphone sensitivity
- [ ] Verify bone conduction speaker clarity
- [ ] Test in noisy environments
- [ ] Check audio latency
- [ ] Verify power consumption during audio playback

## Integration Testing Checklist
- [ ] All components powered correctly
- [ ] No interference between components
- [ ] Stable I2C communication
- [ ] Touch controls working reliably
- [ ] Display visible in various conditions
- [ ] Audio system functioning properly
- [ ] Battery monitoring accurate
- [ ] Temperature within acceptable range
- [ ] All status indicators functional
- [ ] Emergency shutdown working