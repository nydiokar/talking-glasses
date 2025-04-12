#ifndef I2C_HAL_H
#define I2C_HAL_H

#include <Wire.h>
#include "../config/pinmap.h"
#include "../utils/logger.cpp"

class I2cHal {
public:
    static bool init() {
        Logger::debug("I2C", "Initializing I2C on pins SDA: " + String(I2C_SDA) + ", SCL: " + String(I2C_SCL));
        return begin(I2C_SDA, I2C_SCL);
    }

    static bool begin(uint8_t sda, uint8_t scl, uint32_t frequency = 400000) {
        return Wire.begin(sda, scl, frequency);
    }
    
    static void beginTransmission(uint8_t address) {
        Wire.beginTransmission(address);
    }
    
    static uint8_t endTransmission(bool stopBit = true) {
        return Wire.endTransmission(stopBit);
    }
    
    static uint8_t requestFrom(uint8_t address, uint8_t quantity, bool stopBit = true) {
        return Wire.requestFrom(address, quantity, stopBit);
    }
    
    static size_t write(uint8_t data) {
        return Wire.write(data);
    }
    
    static size_t write(const uint8_t* data, size_t quantity) {
        return Wire.write(data, quantity);
    }
    
    static int available() {
        return Wire.available();
    }
    
    static int read() {
        return Wire.read();
    }

    static bool checkDevicePresent(uint8_t address) {
        beginTransmission(address);
        uint8_t error = endTransmission();
        return error == 0; // 0 = success, device present
    }
};

#endif
