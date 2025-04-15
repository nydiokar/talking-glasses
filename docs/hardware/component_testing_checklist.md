# Smart Glasses Component Testing Checklist

Use this checklist to track the testing status of each component in the smart glasses project.

| Component | Tested | Working | Notes | Required Hardware |
|-----------|--------|---------|-------|------------------|
| ESP32-S3 | ✓ | ✓ | Basic functionality working | N/A |
| OLED Display | ✓ | ✓ | Working on pins D8(GPIO17)/D9(GPIO18) | N/A |
| MEMS Microphone | □ | □ | Requires breakout board for testing | INMP441/SPH0645LM4H/ICS-43434 Breakout |
| Touch Sensor | ✓ | ✓ | Built-in on D5(GPIO8), increases values when touched | Wire to D5 pin |
| Battery Monitoring | □ | □ | Voltage divider needed | 2x 10kΩ resistors per battery |
| Bone Conduction | □ | □ | | Audio amplifier module |
| Power Management | □ | □ | | N/A |

## Testing Environment Setup Requirements

1. **MEMS Microphone**:
   - Purchase a MEMS microphone breakout board (INMP441 or SPH0645LM4H recommended)
   - Connect to I2S pins: BCLK(GPIO26), LRCK(GPIO25), DIN(GPIO27)
   - Original tiny MEMS microphone should be saved for final PCB assembly

2. **Battery Monitoring**:
   - Create voltage divider circuits for each battery
   - Use 2x 10kΩ resistors per battery
   - Connect to GPIO34 and GPIO35
   
3. **Touch Sensor**:
   - Connect a wire to pin D5 (GPIO8)
   - Note: Unlike typical touch sensors, this pin's value INCREASES when touched
   - Works directly with ESP32-S3 built-in touch sensing capabilities
   - Threshold needs to be set higher (around 25000) for detection
   
4. **Bone Conduction**:
   - Requires an audio amplifier module
   - Connect to I2S pins: BCLK(GPIO26), LRCK(GPIO25), DOUT(GPIO33)

## Testing Record

| Date | Component | Test Result | Notes |
|------|-----------|-------------|-------|
| | | | |

## Core Components

| Component | Available | Tested | Test File | Notes |
|-----------|:---------:|:------:|-----------|-------|
| ESP32-S3 NANO | □ | □ | N/A | Basic platform |
| OLED Display (SSD1306) | □ | □ | test_display.cpp | |
| MEMS Microphone | □ | □ | | |
| Bone Conduction Speakers | □ | □ | | |
| Mini Spy Camera | □ | □ | | |
| Capacitive Touch Sensor | □ | □ | | |
| LiPo Batteries | □ | □ | | |
| Battery Protection Boards | □ | □ | | |
| I2C Logic Level Converter | □ | □ | test_i2c.cpp | |

## Connectivity Testing

| Interface | Tested | Test File | Notes |
|-----------|:------:|-----------|-------|
| I2C Bus | □ | test_i2c.cpp | For OLED and sensors |
| GPIO Pins | □ | test_gpio.cpp | Basic IO functionality |
| WiFi Connection | □ | | |
| Bluetooth | □ | | |
| Camera Interface | □ | | |
| Audio Output | □ | | |
| Microphone Input | □ | | |
| Touch Sensor Input | □ | | |

## Power Management

| Test | Completed | Notes |
|------|:---------:|-------|
| Battery Life Measurement | □ | |
| Sleep Mode Current Draw | □ | |
| Active Mode Current Draw | □ | |
| Charging Circuit | □ | |

## Test Procedure

1. Check off "Available" when you have the physical component
2. Follow test procedures in the README of each test sketch
3. Mark "Tested" when the component passes all tests
4. Add any comments or issues in the Notes column

## Adding New Tests

1. Create a new test sketch in `src/firmware/test_sketches/`
2. Follow the pattern of existing test files
3. Update this checklist with the new test 