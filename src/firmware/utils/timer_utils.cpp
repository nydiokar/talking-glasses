#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <Arduino.h>

class TimerUtils {
public:
    // Non-blocking delay implementation
    static bool delayElapsed(unsigned long &previousTime, unsigned long interval) {
        unsigned long currentTime = millis();
        if (currentTime - previousTime >= interval) {
            previousTime = currentTime;
            return true;
        }
        return false;
    }
    
    // Get current runtime in milliseconds
    static unsigned long getCurrentTime() {
        return millis();
    }
    
    // Get elapsed time since a given timestamp
    static unsigned long getElapsedTime(unsigned long timestamp) {
        return millis() - timestamp;
    }
    
    // Check if timeout occurred
    static bool hasTimedOut(unsigned long startTime, unsigned long timeout) {
        return (millis() - startTime) >= timeout;
    }
    
    // Safe delay that handles overflow
    static void safeDelay(unsigned long ms) {
        unsigned long start = millis();
        while (millis() - start < ms) {
            yield(); // Allow the ESP32 to handle background tasks
        }
    }
    
    // Convert milliseconds to a readable format (HH:MM:SS.mmm)
    static String formatTime(unsigned long ms) {
        unsigned long seconds = ms / 1000;
        unsigned long minutes = seconds / 60;
        unsigned long hours = minutes / 60;
        
        char buffer[16];
        sprintf(buffer, "%02lu:%02lu:%02lu.%03lu", 
                hours, 
                minutes % 60, 
                seconds % 60, 
                ms % 1000);
        return String(buffer);
    }
};

#endif
