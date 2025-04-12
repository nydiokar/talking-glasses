# Quick Start Guide: Testing Your ESP32-S3-NANO

## Initial Setup (One-Time Only)

1. **Connect your ESP32-S3-NANO to PC**
   - Use a micro-USB cable to connect the board to your computer
   - Make sure the board powers on (you should see an LED light up)

2. **Check Driver Installation**
   - Windows/Linux should automatically recognize the board
   - If not, you may need to install CP210x USB to UART Bridge drivers

3. **Check PlatformIO**
   - Make sure the PlatformIO extension is installed and activated
   - Click the PlatformIO icon in the sidebar (alien/ant icon)
   - Click on "PlatformIO Home" in the menu

## Test 1: I2C Scanner (No External Components Needed)

This is the simplest test - it doesn't require any external components, it just tests if your board can run code.

1. **Click on the PlatformIO icon** in the sidebar
2. **Expand "Project Tasks"**
3. **Expand "env:test_i2c"**
4. **Click "Upload"**
   - This compiles the code and uploads it to your board
   - Watch the terminal at the bottom for progress
   - You should see "Success" when it's done

5. **Click "Monitor"**
   - This opens the serial monitor to see output from your board
   - You should see messages like:
     ```
     [INFO] TEST: I2C Scanner Test Starting
     [INFO] TEST: I2C initialized on pins SDA: 21, SCL: 22
     [INFO] TEST: Scanning I2C bus...
     [WARNING] TEST: No I2C devices found!
     [INFO] TEST: Scan complete. Waiting 5 seconds...
     ```
   - It's normal to see "No I2C devices found" since you haven't connected any I2C devices yet

## Test 2: Add an OLED Display

If you have an OLED display, you can connect it:

1. **Connect the OLED display** to your board:
   - OLED SDA → ESP32 pin D21 (GPIO21)
   - OLED SCL → ESP32 pin D22 (GPIO22)
   - OLED VCC → ESP32 3V3
   - OLED GND → ESP32 GND

2. **Run the I2C Scanner again**
   - Follow the same steps as Test 1
   - This time you should see something like:
     ```
     [INFO] TEST: I2C device found at address 0x3C
     [INFO] TEST:   - Possible OLED display
     ```

3. **Test the Display**
   - Go back to the PlatformIO sidebar
   - Expand "env:test_display"
   - Click "Upload"
   - Click "Monitor"
   - Your OLED display should show some test patterns

## Troubleshooting

If you're having issues:

1. **No upload option in PlatformIO**
   - Try clicking the "Refresh" button in the PlatformIO sidebar
   - Restart VS Code/Cursor

2. **Upload fails with device not found**
   - Check if board is properly connected
   - Try a different USB cable
   - Try a different USB port

3. **Upload succeeds but no serial output**
   - Make sure you click "Monitor" after uploading
   - Check the baud rate is set to 115200
   - Try pressing the reset button on the ESP32 board

4. **"No I2C devices found" even with OLED connected**
   - Double-check your wiring
   - Try different pins (update the pinmap.h file if needed)
   - Make sure the OLED is powered (3.3V) 