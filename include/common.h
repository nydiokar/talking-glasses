#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

// Common error codes
enum ErrorCode {
    ERROR_NONE = 0,
    ERROR_INIT_FAILED,
    ERROR_CONNECTION_FAILED,
    ERROR_TIMEOUT,
    ERROR_INVALID_PARAM,
    ERROR_OUT_OF_MEMORY,
    ERROR_NOT_SUPPORTED,
    ERROR_NOT_INITIALIZED,
    ERROR_HARDWARE_FAULT
};

// System states
enum SystemState {
    STATE_BOOT,
    STATE_INIT,
    STATE_CONNECTING,
    STATE_READY,
    STATE_LISTENING,
    STATE_PROCESSING,
    STATE_RESPONDING,
    STATE_ERROR,
    STATE_LOW_POWER,
    STATE_SLEEP
};

// Message types for inter-module communication
enum MessageType {
    MSG_NONE,
    MSG_COMMAND,
    MSG_RESPONSE,
    MSG_ERROR,
    MSG_STATUS,
    MSG_POWER,
    MSG_TOUCH,
    MSG_AUDIO,
    MSG_DISPLAY
};

// Message structure for inter-module communication
struct Message {
    MessageType type;
    uint32_t timestamp;
    String data;
    int param1;
    int param2;
    void* ptr;
};

// Function result with error handling
template<typename T>
struct Result {
    T value;
    ErrorCode error;
    bool success;

    static Result<T> ok(T val) {
        return {val, ERROR_NONE, true};
    }

    static Result<T> fail(ErrorCode err) {
        return {T(), err, false};
    }
};

// Version information
#define FW_VERSION_MAJOR 1
#define FW_VERSION_MINOR 0
#define FW_VERSION_PATCH 0
#define FW_VERSION_STRING "1.0.0"

// Helper macros
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CONCAT(a, b) a ## b

// Debug macros (can be disabled in production)
#ifdef DEBUG_ENABLED
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

#endif // COMMON_H 