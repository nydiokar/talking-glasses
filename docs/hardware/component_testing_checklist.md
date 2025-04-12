# Component Testing Checklist

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