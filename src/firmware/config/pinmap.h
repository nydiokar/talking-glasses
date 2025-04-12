#ifndef PINMAP_H
#define PINMAP_H

// OLED Display pins
#define OLED_SDA 8
#define OLED_SCL 9

// I2C Bus pins (used by I2C_HAL)
#define I2C_SDA OLED_SDA
#define I2C_SCL OLED_SCL

// Audio pins
#define I2S_BCLK 26
#define I2S_LRCK 25
#define I2S_DOUT 33
#define I2S_DIN 27

// Touch sensor pin
#define TOUCH_PIN 7

// Battery monitoring pins
#define BAT1_VOLTAGE_PIN 34
#define BAT2_VOLTAGE_PIN 35

// LED indicators
#define STATUS_LED 48  // Onboard red LED


// Button pins
#define BUTTON_POWER 13
#define BUTTON_MODE 12

#endif
