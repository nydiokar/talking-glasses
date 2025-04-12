#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

#include <driver/i2s.h>
#include "kiss_fft.h"
#include "../modules/network_module.cpp"

#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define SAMPLE_RATE 16000
#define BUFFER_SIZE 1024

class AudioDriver {
public:
    bool begin() {
        // Configure I2S for MEMS microphone
        i2s_config_t i2s_config = {
            .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
            .sample_rate = SAMPLE_RATE,
            .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = I2S_COMM_FORMAT_STAND_I2S,
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 4,
            .dma_buf_len = BUFFER_SIZE,
            .use_apll = false
        };
        
        i2s_pin_config_t pin_config = {
            .bck_io_num = I2S_SCK,
            .ws_io_num = I2S_WS,
            .data_out_num = I2S_PIN_NO_CHANGE,
            .data_in_num = I2S_SD
        };
        
        esp_err_t err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
        if (err != ESP_OK) return false;
        
        err = i2s_set_pin(I2S_NUM_0, &pin_config);
        return err == ESP_OK;
    }
    
    bool voiceDetected() {
        int16_t samples[BUFFER_SIZE];
        size_t bytes_read;
        
        i2s_read(I2S_NUM_0, samples, sizeof(samples), &bytes_read, portMAX_DELAY);
        
        // Simple energy-based voice activity detection
        float energy = 0;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            energy += abs(samples[i]);
        }
        energy /= BUFFER_SIZE;
        
        return energy > VOICE_THRESHOLD;
    }
    
    String getVoiceCommand() {
        // Record audio for command
        size_t audioSize = SAMPLE_RATE * 2; // 2 seconds of audio
        int16_t* audioBuffer = new int16_t[audioSize];
        
        size_t bytes_read;
        size_t totalRead = 0;
        
        while (totalRead < audioSize * sizeof(int16_t)) {
            i2s_read(I2S_NUM_0, 
                    ((uint8_t*)audioBuffer) + totalRead, 
                    audioSize * sizeof(int16_t) - totalRead, 
                    &bytes_read, 
                    portMAX_DELAY);
            totalRead += bytes_read;
        }
        
        // Send audio to server for processing
        bool success = networkModule->sendAudio((uint8_t*)audioBuffer, audioSize * sizeof(int16_t));
        delete[] audioBuffer;
        
        if (!success) {
            return "Error processing audio";
        }
        
        // Wait for response
        delay(100);
        return "Command processed"; // Actual response should come from server
    }
    
    void playResponse(const String &text) {
        // Implementation for bone conduction audio output
        // This would typically use I2S or DAC output
        // Actual implementation depends on your bone conduction speaker setup
    }
    
    void toggleMute() {
        isMuted = !isMuted;
        // Implement mute functionality
    }
    
private:
    static const float VOICE_THRESHOLD = 1000.0;
    bool isMuted = false;
    NetworkModule* networkModule;
};

#endif
