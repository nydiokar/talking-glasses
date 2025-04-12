# AI Glasses

Smart glasses powered by ESP32-S3 with cloud-based AI processing capabilities.

## Overview

The AI Glasses project combines wearable hardware with cloud-based AI services to provide a voice and vision-assisted experience. The system captures audio and visual input from the user's environment, processes it on a remote server, and provides feedback through bone conduction audio and an OLED display.

### Key Features

- **Voice Recognition**: Captures voice commands via MEMS microphone
- **Image Processing**: Captures images for object detection and scene description
- **Bone Conduction Audio**: Delivers audio responses without blocking environmental sounds
- **Gesture Control**: Touch-based interface for controlling device functions
- **Efficient Power Management**: Multiple power modes to extend battery life
- **Compact Design**: All components integrated into a glasses form factor

## Hardware Requirements

- ESP32-S3 microcontroller
- MEMS microphone
- SSD1306 OLED display
- OV2640 camera module
- Bone conduction transducer
- Touch sensor
- Dual battery power system
- WiFi connectivity

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