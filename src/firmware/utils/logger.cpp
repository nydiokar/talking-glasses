#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogLevel {
    LOG_NONE = 0,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_VERBOSE
};

class Logger {
public:
    static void init(LogLevel level = LOG_INFO, unsigned long baud = 115200) {
        currentLevel = level;
        Serial.begin(baud);
        while (!Serial && millis() < 3000); // Wait for Serial up to 3 seconds
        Serial.println("[Logger] Initialized");
    }
    
    static void setLogLevel(LogLevel level) {
        currentLevel = level;
    }
    
    static void log(LogLevel level, const char* module, const char* message) {
        if (level <= currentLevel) {
            unsigned long now = millis();
            Serial.print("[");
            Serial.print(now);
            Serial.print("] ");
            
            switch(level) {
                case LOG_ERROR:
                    Serial.print("ERROR");
                    break;
                case LOG_WARNING:
                    Serial.print("WARNING");
                    break;
                case LOG_INFO:
                    Serial.print("INFO");
                    break;
                case LOG_DEBUG:
                    Serial.print("DEBUG");
                    break;
                case LOG_VERBOSE:
                    Serial.print("VERBOSE");
                    break;
                default:
                    break;
            }
            
            Serial.print(" [");
            Serial.print(module);
            Serial.print("] ");
            Serial.println(message);
        }
    }
    
    static void log(LogLevel level, const char* module, const String& message) {
        log(level, module, message.c_str());
    }
    
    static void error(const char* module, const char* message) {
        log(LOG_ERROR, module, message);
    }
    
    static void error(const char* module, const String& message) {
        log(LOG_ERROR, module, message);
    }
    
    static void warning(const char* module, const char* message) {
        log(LOG_WARNING, module, message);
    }
    
    static void warning(const char* module, const String& message) {
        log(LOG_WARNING, module, message);
    }
    
    static void info(const char* module, const char* message) {
        log(LOG_INFO, module, message);
    }
    
    static void info(const char* module, const String& message) {
        log(LOG_INFO, module, message);
    }
    
    static void debug(const char* module, const char* message) {
        log(LOG_DEBUG, module, message);
    }
    
    static void debug(const char* module, const String& message) {
        log(LOG_DEBUG, module, message);
    }
    
    static void verbose(const char* module, const char* message) {
        log(LOG_VERBOSE, module, message);
    }
    
    static void verbose(const char* module, const String& message) {
        log(LOG_VERBOSE, module, message);
    }
    
private:
    static LogLevel currentLevel;
};

LogLevel Logger::currentLevel = LOG_INFO;

#endif
