#ifndef I2S_HAL_H
#define I2S_HAL_H

#include <driver/i2s.h>

class I2sHal {
public:
    static esp_err_t init(i2s_port_t port, const i2s_config_t *config) {
        return i2s_driver_install(port, config, 0, NULL);
    }
    
    static esp_err_t setPins(i2s_port_t port, const i2s_pin_config_t *pins) {
        return i2s_set_pin(port, pins);
    }
    
    static esp_err_t read(i2s_port_t port, void *dest, size_t size, size_t *bytes_read, TickType_t ticks_to_wait) {
        return i2s_read(port, dest, size, bytes_read, ticks_to_wait);
    }
    
    static esp_err_t write(i2s_port_t port, const void *src, size_t size, size_t *bytes_written, TickType_t ticks_to_wait) {
        return i2s_write(port, src, size, bytes_written, ticks_to_wait);
    }
    
    static esp_err_t setClk(i2s_port_t port, uint32_t rate, i2s_bits_per_sample_t bits, i2s_channel_t ch) {
        return i2s_set_clk(port, rate, bits, ch);
    }
    
    static esp_err_t stop(i2s_port_t port) {
        return i2s_stop(port);
    }
    
    static esp_err_t start(i2s_port_t port) {
        return i2s_start(port);
    }
};

#endif
