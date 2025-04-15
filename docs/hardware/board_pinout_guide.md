# ESP32-S3-NANO Board Pin Mapping Guide

## Board to Code Pin Mapping

Looking at your ESP32-S3-NANO board, here's how the physical pins map to our code:

| Physical Pin Label | Code Pin Number | Used For | Tested |
|-------------------|-----------------|----------|--------|
| D0 | GPIO3 | - | |
| D1 | GPIO4 | - | |
| D2 | GPIO5 | - | ✓ |
| D3 | GPIO6 | - | ✓ |
| D4 | GPIO7 | - | ✓ |
| D5 | GPIO8 | Touch Sensor | ✓ |
| D6 | GPIO9 | - | ✓ |
| D7 | GPIO10 | - | |
| D8 | GPIO17 | I2C SDA | ✓ |
| D9 | GPIO18 | I2C SCL | ✓ |
| D10 | GPIO10 | - | |
| D11 | GPIO11 | - | |
| D12 | GPIO12 | - | |
| D13 | GPIO13 | - | |
| D14 | GPIO14 | - | |
| TX | GPIO43 | - | |
| RX | GPIO44 | - | |
| A0 | GPIO1 | - | |
| A1 | GPIO2 | - | |
| A2 | GPIO3 | - | |
| A3 | GPIO4 | - | |
| A4 | GPIO5 | - | |
| A5 | GPIO6 | - | |
| A6 | GPIO7 | - | |
| A7 | GPIO8 | - | |
| GND | Ground | Ground | ✓ |
| 3V3 | 3.3V | Power | ✓ |
| 5V | 5V | Power | |
| (Internal) | GPIO48 | STATUS_LED (Red onboard LED) | ✓ |

## I2C Connection (for OLED and other I2C devices)

For the I2C test, connect:

1. SDA (Serial Data) → Connect to pin **D8** (GPIO17) on your board (TESTED & WORKING)
2. SCL (Serial Clock) → Connect to pin **D9** (GPIO18) on your board (TESTED & WORKING)
3. VCC → Connect to **3V3** on your board
4. GND → Connect to **GND** on your board

**Note:** The physical pins labeled D8/D9 on the board correspond to GPIO17/GPIO18 in software.

## Onboard LED Information

This board has a single red status LED:
- Connected to GPIO48 (internal, not directly accessible via pin headers)
- Active LOW logic (write LOW to turn ON, write HIGH to turn OFF)

**Note:** Despite what was indicated in previous documentation, this board does not have an RGB LED. It only has a single red LED for status indication, and it's on GPIO48 (not GPIO2 as previously thought).

## Step-by-Step Testing Guide

### Getting Started:

1. **Connect your ESP32-S3-NANO to PC**: 
   - Use a micro-USB cable to connect the board to your computer
   - Windows should recognize it as a COM port device

2. **Select the COM port in PlatformIO**:
   - In the PlatformIO sidebar, click on "PlatformIO Home"
   - Go to "Devices" and note which COM port your board is connected to
   - If needed, update the upload_port in platformio.ini:
     ```
     upload_port = COM3  ; Change to your actual COM port
     ```

3. **Run your first test** (I2C Scanner):
   - In the PlatformIO sidebar, click on the PlatformIO icon
   - Under "Project Tasks", expand "env:i2c_test"
   - Click "Upload" to compile and upload the test
   - After successful upload, click "Monitor" to see the serial output

If you're not seeing any output in the monitor, make sure:
1. The board is properly connected via USB
2. You've selected the correct environment in PlatformIO
3. The monitor speed is set to 115200 baud

## Wiring Diagram for I2C Test

```
ESP32-S3-NANO Board          OLED Display
-----------------          -------------
     D8 (GPIO17) --------> SDA  (TESTED & WORKING)
     D9 (GPIO18) --------> SCL  (TESTED & WORKING)
     3V3 ---------------------> VCC
     GND ---------------------> GND
```

## Tested Functionality

The following has been tested and confirmed working:
- Basic serial communication
- Status LED (GPIO48) - single red LED, active LOW
- I2C functionality on pins D8/D9 (GPIO8/GPIO9)

## Pin Mapping Pattern

There's a pattern in how physical pin labels map to GPIO numbers:

1. For pins D0-D7: The GPIO number is D-number + 3
   - For example: D2 connects to GPIO5 (2+3), D5 connects to GPIO8 (5+3)

2. For pins D8-D9: These connect to GPIO17 and GPIO18 respectively

This pattern is important when writing code that needs to access specific pins, as you must use the GPIO number, not the physical pin label. 