#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <Arduino.h>

class GpioHal {
public:
    static void configurePin(uint8_t pin, uint8_t mode) {
        pinMode(pin, mode);
    }
    
    static void digitalWrite(uint8_t pin, uint8_t value) {
        ::digitalWrite(pin, value);
    }
    
    static int digitalRead(uint8_t pin) {
        return ::digitalRead(pin);
    }
    
    static void attachInterrupt(uint8_t pin, void (*callback)(), int mode) {
        ::attachInterrupt(pin, callback, mode);
    }
    
    static void detachInterrupt(uint8_t pin) {
        ::detachInterrupt(pin);
    }
};

#endif
