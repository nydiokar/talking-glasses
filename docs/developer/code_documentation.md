# Smart Glasses Code Documentation

## Project Structure
```
talking-glasses/
├── docs/                  # Documentation files
├── src/
│   ├── firmware/          # ESP32-S3 firmware source
│   │   ├── main/          # Entry point and main loop
│   │   ├── config/        # Board-specific configurations
│   │   ├── hal/           # Hardware Abstraction Layer
│   │   ├── drivers/       # Peripheral drivers (I2C, I2S, etc.)
│   │   ├── modules/       # Functional modules (audio, display, etc.)
│   │   └── utils/         # Utility functions and helpers
│   ├── server/            # AI server implementation
│   └── models/            # 3D printing files
├── include/               # Shared headers
├── boards/                # Board-specific configurations
├── platformio.ini         # PlatformIO configuration file
└── README.md              # Project overview and setup instructions
```
## Overview of the structure

🧩 Key Components
1. Main Application (main/)
main.cpp: Initializes the system, starts the scheduler, and manages the main loop.​

2. Configuration (config/)

pinmap.h: Defines GPIO assignments for peripherals.​
config.h: Holds global configuration macros and settings.​

3. Hardware Abstraction Layer (hal/)
Purpose: Provides a uniform interface to hardware functionalities, facilitating portability.​

Examples:
gpio_hal.cpp: Manages GPIO operations.​
i2c_hal.cpp: Handles I2C communication.​
i2s_hal.cpp: Manages I2S audio interface.​

4. Peripheral Drivers (drivers/)
Purpose: Implements low-level drivers for specific peripherals.​

Examples:
display_driver.cpp: Controls OLED display operations.​
audio_driver.cpp: Manages audio input/output.​

5. Functional Modules (modules/)
Purpose: Encapsulates high-level functionalities.​

Examples:
audio_module.cpp: Handles audio processing and voice detection.​
network_module.cpp: Manages Wi-Fi and server communications.​
touch_module.cpp: Processes touch input and gestures.​
power_module.cpp: Manages power and battery operations.​

6. Utilities (utils/)
Purpose: Provides helper functions and common utilities.​

Examples:
logger.cpp: Handles logging and debugging outputs.​
timer_utils.cpp: Manages timing operations.​



## Firmware Components

### main.cpp
- **Purpose**: Main firmware entry point - initializes the system, starts the scheduler, and manages the main loop.​
- **Key Functions**:
  * System initialization
  * Component management
  * Main loop implementation
  * Event handling

### gpio_hal.cpp
- **Purpose**: GPIO hardware abstraction
- **Features**:
  * Pin configuration
  * Input/output control
  * Interrupt handling
  * Power state management
  * Signal debouncing

### i2c_hal.cpp
- **Purpose**: I2C communication interface
- **Features**:
  * Bus initialization
  * Device addressing
  * Data transmission
  * Error handling
  * Clock management

### i2s_hal.cpp
- **Purpose**: I2S audio interface
- **Features**:
  * Audio stream configuration
  * Clock synchronization
  * DMA transfers
  * Sample rate management
  * Channel control

### display_driver.cpp
- **Purpose**: OLED display control
- **Features**:
  * Status display
  * Text rendering
  * Error messages
  * Battery status
  * Power management integration

### network_module.cpp
- **Purpose**: WiFi and server communication
- **Features**:
  * WiFi connection handling
  * Server communication
  * Data transmission
  * Error recovery
  * Security implementation

### audio_driver.cpp
- **Purpose**: Audio input/output control
- **Features**:
  * Voice detection
  * Audio recording
  * Bone conduction output
  * Audio processing
  * Power optimization

### touch_module.cpp
- **Purpose**: Touch input handling
- **Features**:
  * Gesture recognition
  * Touch event processing
  * Multi-touch support
  * Power-efficient polling

### power_module.cpp
- **Purpose**: Power and battery management
- **Features**:
  * Dual battery monitoring
  * Power mode switching
  * Voltage monitoring
  * Battery life optimization
  * Low power modes

### logger.cpp
- **Purpose**: System logging utility
- **Features**:
  * Multi-level logging
  * Console output
  * Flash storage logging
  * Error reporting
  * Performance metrics

### timer_utils.cpp
- **Purpose**: Timing operations management
- **Features**:
  * Precise delays
  * Event scheduling
  * Timeout handling
  * Power-aware timing
  * Synchronization utilities

## Server Components

### main.py
- **Purpose**: Server entry point
- **Features**:
  * FastAPI setup
  * Router integration
  * WebSocket support
  * SSL configuration
  * Logging setup

### app/models/ai_manager.py
- **Purpose**: AI model management
- **Features**:
  * Model initialization
  * Whisper integration
  * YOLO implementation
  * Ollama/Mistral integration
  * Resource management

### app/routers/audio.py
- **Purpose**: Audio processing endpoints
- **Features**:
  * Audio file processing
  * Speech-to-text
  * Audio response generation
  * Error handling

### app/routers/vision.py
- **Purpose**: Image processing endpoints
- **Features**:
  * Image analysis
  * Object detection
  * Scene description
  * Visual processing

### app/routers/chat.py
- **Purpose**: Text chat endpoints
- **Features**:
  * Real-time chat
  * WebSocket handling
  * Query processing
  * Response generation

### app/security.py
- **Purpose**: Security implementation
- **Features**:
  * API key management
  * JWT implementation
  * IP blocking
  * Request validation
  * SSL configuration
  * Key rotation
  * Session management

## Key Features Implementation

### Voice Processing Pipeline
1. Audio captured via MEMS microphone
2. Processed by ESP32-S3
3. Sent to server via WebSocket
4. Processed by Whisper model
5. Response generated by Mistral
6. Sent back to glasses
7. Played through bone conduction

### Vision Processing Pipeline
1. Image captured by camera
2. Sent to server
3. Processed by YOLO
4. Objects detected and classified
5. Optional text description generated
6. Results sent back to glasses
7. Displayed on OLED

### Power Management System
1. Dual battery monitoring
2. Automatic power mode switching
3. Component-level power optimization
4. Temperature monitoring
5. Voltage regulation
6. Emergency shutdown procedures

### Security Implementation
1. Local network restriction
2. API key validation
3. JWT authentication
4. SSL/TLS encryption
5. IP blocking
6. Request rate limiting
7. Key rotation system

## Configuration Notes

### ESP32-S3 Pins
- OLED: I2C (SDA: 17, SCL: 18)
- Audio: I2S (BCLK: 26, LRCK: 25, DOUT: 33)
- Touch: GPIO4
- Battery Monitoring: GPIO34, GPIO35

### Server Configuration
- Default port: 8000
- SSL required
- Local network only
- Rate limiting enabled
- Automatic model loading

## Development Notes

### Build Requirements
1. Arduino IDE or PlatformIO
2. Python 3.8+
3. CUDA-capable GPU
4. Required Python packages in requirements.txt

### Testing Procedures
1. Component-level testing
2. Integration testing
3. Power consumption testing
4. Network reliability testing
5. Security testing

This documentation provides an overview of the current codebase. As development continues, it should be updated to reflect any changes or additions to the system.