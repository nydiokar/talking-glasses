# Smart Glasses Project

Smart glasses powered by ESP32-S3 with cloud-based AI processing capabilities.

## Overview

The Smart Glasses project combines wearable hardware with cloud-based AI services to provide a voice and vision-assisted experience. The system captures audio and visual input from the user's environment, processes it on a remote server, and provides feedback through bone conduction audio and an OLED display.

### Key Features

- **Voice Recognition**: Captures voice commands via MEMS microphone
- **Image Processing**: Captures images for object detection and scene description
- **Bone Conduction Audio**: Delivers audio responses without blocking environmental sounds
- **Gesture Control**: Touch-based interface for controlling device functions
- **Efficient Power Management**: Multiple power modes to extend battery life
- **Compact Design**: All components integrated into a glasses form factor

## Hardware Configuration

### Confirmed Hardware Pinout

| Component | GPIO Pin | Physical Pin | Notes |
|-----------|----------|--------------|-------|
| Status LED | GPIO48 | (Internal) | Red LED, active LOW |
| I2C SDA | GPIO8 | D8 | For OLED display and sensors |
| I2C SCL | GPIO9 | D9 | For OLED display and sensors |

## Getting Started

### Prerequisites

- PlatformIO installed in VSCode/Cursor
- ESP32-S3 development board
- USB cable

### Setup

1. Clone this repository
2. Open in VSCode/Cursor with PlatformIO installed
3. Configure your COM port in `platformio.ini` if needed:
   ```ini
   upload_port = COMx  # Replace with your actual port
   ```

### Testing

We have several test sketches to verify hardware functionality:

- `basic_test`: Simple serial communication test
- `i2c_test`: Tests I2C functionality on pins GPIO8/9
- `status_led_blink`: Tests the onboard LED on GPIO48

To run a test:

1. Select the appropriate environment in PlatformIO
2. Click "Upload" to compile and upload the test
3. Open Serial Monitor to see output (115200 baud)

## Development Guidelines

- Keep commits small and focused
- Write meaningful commit messages
- Add tests for new functionality
- Update documentation as you go

## Project Structure

- `src/firmware/`: Core firmware components
  - `drivers/`: Hardware-specific driver code
  - `hal/`: Hardware abstraction layer
  - `modules/`: Functional modules
  - `utils/`: Shared utilities
  - `config/`: Configuration files
  - `test_sketches/`: Individual test programs

## Software Architecture

The firmware follows a modular architecture:

- **Main Application**: Core system loop and component coordination
- **HAL Layer**: Hardware abstraction for portability
- **Drivers**: Low-level peripheral control
- **Modules**: High-level functional components
- **Utilities**: Shared helper functions

The server-side includes:

- **Speech-to-Text**: Whisper model for voice command processing
- **Vision Processing**: YOLO for object detection
- **LLM Integration**: Mistral/Ollama for intelligent responses
- **API Layer**: FastAPI for communication with the glasses

## Setup Instructions

### Development Environment Setup

1. Install PlatformIO (recommended) or Arduino IDE
2. Clone this repository
3. Open the project in your IDE

### Building the Firmware

```bash
# Using PlatformIO CLI
platformio run

# For a specific environment
platformio run -e esp32s3
```

### Uploading to Device

```bash
# Using PlatformIO CLI
platformio run -t upload

# For a specific port
platformio run -t upload --upload-port COM3
```

### Server Setup

1. Navigate to the server directory
2. Install requirements:
   ```bash
   pip install -r requirements.txt
   ```
3. Run the server:
   ```bash
   python main.py
   ```

## Configuration

- Edit `config.h` for system-wide settings
- Edit `pinmap.h` for GPIO assignments
- Set your WiFi credentials in the main app or through the configuration portal

## Contributing

Contributions are welcome! Please see the contributing guidelines before submitting pull requests.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- ESP32 Community
- Open source AI model providers
- All contributors 