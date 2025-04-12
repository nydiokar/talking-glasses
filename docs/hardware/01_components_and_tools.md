# DIY AI-Powered Smart Glasses: Components and Tools Guide

## Core Electronics

### 1. Processing & Communication
* ESP32-S3 NANO (Wi-Fi/Bluetooth module): ~$10-$15
* OLED Display (128x32 or 128x64 SSD1306): ~$5-10
* Capacitive Touch Sensor (TTP223 or similar): ~$3-5
* I2C Logic Level Converter (for OLED): ~$2

### 2. Input/Output Devices
* MEMS Microphone (for voice commands): ~$5-$10
* Bone Conduction Speakers: ~$30-$50
* Mini Spy Camera (for vision tasks): ~$20-$40

### 3. Power System
* LiPo Batteries (2x 1000mAh for split design): ~$10-$30
* Battery Protection Boards (2x): ~$4
* Power Distribution Board (optional): ~$5

## Wiring and Connectors
* Jumper wires (various sizes)
* Heat-shrink tubing (various diameters)
* Micro USB or USB-C cables
* I2C cables for OLED
* Flat flex cables for touch sensor
* JST connectors for batteries
* Silicon-coated thin gauge wire

## Miscellaneous Components
* Breadboard (for initial testing): ~$5
* Various adhesives:
  - UV-curable clear epoxy
  - Double-sided tape (thin)
  - Thermal adhesive for heat sinks
* Heat sinks for ESP32-S3 (optional)
* Anti-reflection coating (for OLED)
* Optical clear adhesive (for display mounting)

## Tools Required

### 1. Hardware Tools
* Soldering station with temperature control
* Hot air rework station (recommended)
* Wire cutters/strippers
* Precision screwdriver set
* Multimeter
* Digital caliper
* Magnifying glass/loupe
* Tweezers set
* Heat gun
* UV light (for UV-curable adhesives)

### 2. Software Tools
* TinkerCAD: Circuit design and basic mockups
* Fusion 360: Frame design and component fitting
* Arduino IDE: ESP32-S3 programming
* Python 3.8+: Server-side development
* Visual Studio Code: Code editing
* 3D Printer Software
* PlatformIO IDE (recommended alternative to Arduino IDE)

## Desktop Computer Requirements
* CPU: Modern multi-core processor
* GPU: RTX 3090/4090 (for local AI processing)
* RAM: 32GB+ 
* Storage: 1TB+ SSD
* OS: Windows/Linux (WSL2 recommended for Windows)

## Component Selection Tips
1. Always order from reputable suppliers to ensure component quality
2. Purchase extra components for critical parts (ESP32-S3, OLED, touch sensors)
3. Verify component dimensions before ordering to ensure fit in frames
4. Check component compatibility with ESP32-S3 and required libraries
5. Consider ordering a few different OLED displays to test visibility
6. Get batteries with built-in protection circuits when possible