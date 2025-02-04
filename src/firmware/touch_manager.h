#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

enum TouchGesture {
    NONE,
    SINGLE_TAP,
    DOUBLE_TAP,
    LONG_PRESS,
    SWIPE_LEFT,
    SWIPE_RIGHT
};

class TouchManager {
public:
    bool begin() {
        pinMode(TOUCH_PIN, INPUT);
        touchAttachInterrupt(TOUCH_PIN, nullptr, TOUCH_THRESHOLD);
        return true;
    }
    
    bool checkTouch() {
        uint16_t touchValue = touchRead(TOUCH_PIN);
        unsigned long currentTime = millis();
        
        if (touchValue < TOUCH_THRESHOLD) {
            if (!isTouching) {
                touchStartTime = currentTime;
                isTouching = true;
            } else {
                // Check for long press
                if (currentTime - touchStartTime > LONG_PRESS_DURATION) {
                    currentGesture = LONG_PRESS;
                    return true;
                }
            }
        } else {
            if (isTouching) {
                // Touch released
                unsigned long touchDuration = currentTime - touchStartTime;
                
                if (touchDuration < TAP_DURATION) {
                    // Potential tap
                    if (currentTime - lastTapTime < DOUBLE_TAP_INTERVAL) {
                        currentGesture = DOUBLE_TAP;
                        lastTapTime = 0;
                        return true;
                    } else {
                        lastTapTime = currentTime;
                        // Wait a bit to see if it's a double tap
                        delay(50);
                        if (touchRead(TOUCH_PIN) >= TOUCH_THRESHOLD) {
                            currentGesture = SINGLE_TAP;
                            return true;
                        }
                    }
                }
                isTouching = false;
            }
        }
        
        return false;
    }
    
    TouchGesture getGesture() {
        TouchGesture gesture = currentGesture;
        currentGesture = NONE;
        return gesture;
    }
    
private:
    static const uint8_t TOUCH_PIN = 4;
    static const uint16_t TOUCH_THRESHOLD = 40;
    static const unsigned long TAP_DURATION = 150;
    static const unsigned long DOUBLE_TAP_INTERVAL = 300;
    static const unsigned long LONG_PRESS_DURATION = 500;
    
    bool isTouching = false;
    unsigned long touchStartTime = 0;
    unsigned long lastTapTime = 0;
    TouchGesture currentGesture = NONE;
    float lastTouchX = 0;
};

#endif