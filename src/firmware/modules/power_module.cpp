#ifndef POWER_MODULE_H
#define POWER_MODULE_H

enum PowerMode {
    NORMAL,
    ECO,
    ULTRA_LOW
};

class PowerModule {
public:
    bool begin() {
        // Configure ADC for battery monitoring
        analogReadResolution(12);
        analogSetAttenuation(ADC_11db);
        
        // Configure power pins
        pinMode(BAT1_VOLTAGE_PIN, INPUT);
        pinMode(BAT2_VOLTAGE_PIN, INPUT);
        
        return true;
    }
    
    void checkStatus() {
        unsigned long currentTime = millis();
        if (currentTime - lastCheck < CHECK_INTERVAL) {
            return;
        }
        lastCheck = currentTime;
        
        // Read battery voltages
        float bat1Voltage = readBatteryVoltage(BAT1_VOLTAGE_PIN);
        float bat2Voltage = readBatteryVoltage(BAT2_VOLTAGE_PIN);
        
        // Update battery levels
        bat1Level = voltageToPercent(bat1Voltage);
        bat2Level = voltageToPercent(bat2Voltage);
        
        // Check if we need to switch power modes
        updatePowerMode();
    }
    
    bool needsAttention() {
        return bat1Level < LOW_BATTERY_THRESHOLD || 
               bat2Level < LOW_BATTERY_THRESHOLD;
    }
    
    void togglePowerMode() {
        switch (currentMode) {
            case NORMAL:
                currentMode = ECO;
                break;
            case ECO:
                currentMode = ULTRA_LOW;
                break;
            case ULTRA_LOW:
                currentMode = NORMAL;
                break;
        }
        applyPowerMode();
    }
    
    float getBatteryLevel() {
        return min(bat1Level, bat2Level);
    }
    
private:
    static const uint8_t BAT1_VOLTAGE_PIN = 34;
    static const uint8_t BAT2_VOLTAGE_PIN = 35;
    static const unsigned long CHECK_INTERVAL = 30000; // 30 seconds
    static const float LOW_BATTERY_THRESHOLD = 20.0;
    static const float CRITICAL_BATTERY_THRESHOLD = 10.0;
    
    PowerMode currentMode = NORMAL;
    float bat1Level = 100.0;
    float bat2Level = 100.0;
    unsigned long lastCheck = 0;
    
    float readBatteryVoltage(uint8_t pin) {
        // Read ADC and convert to voltage
        float adcValue = analogRead(pin);
        return (adcValue / 4095.0) * 3.3 * 2; // Voltage divider ratio
    }
    
    float voltageToPercent(float voltage) {
        // LiPo battery voltage to percentage conversion
        // Assuming 3.0V = 0%, 4.2V = 100%
        float percentage = (voltage - 3.0) * 83.33;
        return constrain(percentage, 0, 100);
    }
    
    void updatePowerMode() {
        float minBattery = min(bat1Level, bat2Level);
        
        if (minBattery < CRITICAL_BATTERY_THRESHOLD) {
            currentMode = ULTRA_LOW;
        } else if (minBattery < LOW_BATTERY_THRESHOLD) {
            currentMode = ECO;
        }
        
        applyPowerMode();
    }
    
    void applyPowerMode() {
        switch (currentMode) {
            case NORMAL:
                // Full functionality
                setCpuFrequencyMhz(240);
                break;
                
            case ECO:
                // Reduced functionality
                setCpuFrequencyMhz(160);
                break;
                
            case ULTRA_LOW:
                // Minimal functionality
                setCpuFrequencyMhz(80);
                break;
        }
    }
};

#endif
