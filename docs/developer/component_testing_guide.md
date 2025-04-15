# Component Testing Guide

This guide outlines how to test each component of your Smart Glasses project using PlatformIO.

## Prerequisites

1. PlatformIO extension installed in VSCode/Cursor
2. ESP32-S3 board connected via USB
3. Components to test (refer to the component checklist)

## General Testing Procedure

1. Connect your ESP32-S3 to your computer
2. Connect the component you want to test according to the pinout in `src/firmware/config/pinmap.h`
3. Select the appropriate test environment in PlatformIO
4. Build and upload the test code
5. Open the Serial Monitor to view test results

## Available Tests

### 1. I2C Scanner Test

**Purpose**: Scan the I2C bus and detect connected devices (OLED display, sensors, etc.)

**Setup**:
1. Connect SDA to pin 17 and SCL to pin 18 on ESP32-S3
2. Connect any I2C devices you want to test

**How to Run**:
1. In PlatformIO sidebar, select `test_i2c` environment
2. Click Upload
3. Open Serial Monitor at 115200 baud
4. The test will scan for I2C devices and report their addresses

**Expected Results**:
- For OLED Display: Should detect device at 0x3C or 0x3D
- Results are shown in Serial Monitor

### 2. Display Test

**Purpose**: Test OLED display functionality

**Setup**:
1. Connect SDA to pin 17 and SCL to pin 18 on ESP32-S3
2. Connect OLED display VCC to 3.3V and GND to ground

**How to Run**:
1. In PlatformIO sidebar, select `test_display` environment
2. Click Upload
3. Open Serial Monitor at 115200 baud

**Expected Results**:
- Display should initialize and show test patterns
- Serial monitor will report success or errors

### 3. GPIO Test

**Purpose**: Test basic GPIO functionality

**Setup**:
1. For LED test: Connect an LED with a resistor to pin 2
2. For button test: Connect buttons to pins 12 and 13

**How to Run**:
1. In PlatformIO sidebar, select `test_gpio` environment
2. Click Upload
3. Open Serial Monitor at 115200 baud

**Expected Results**:
- LED should blink
- Button presses should be detected
- Results are shown in Serial Monitor

## Troubleshooting Common Issues

### No Devices Found on I2C Bus
- Check wiring connections
- Verify power supply to I2C devices (3.3V)
- Try different I2C pull-up resistors (4.7k-10k ohm)
- Reduce I2C clock speed by modifying `I2cHal::begin` frequency parameter

### Display Not Working
- Verify I2C address (use I2C scanner test)
- Check power connections
- Try different OLED libraries if necessary

### GPIO Issues
- Check for proper pin configuration
- Ensure pins are not in use by other peripherals
- Verify pull-up/pull-down resistors if using buttons

## Creating New Tests

1. Create a new test file in `src/firmware/test_sketches/`
2. Add a new environment in `platformio.ini`
3. Follow the pattern of existing tests
4. Update the testing checklist 