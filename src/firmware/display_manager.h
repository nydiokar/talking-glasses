#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
public:
    DisplayManager() : display(128, 32, &Wire, -1) {}
    
    bool begin() {
        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            return false;
        }
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.display();
        return true;
    }
    
    void showStatus(const String &status) {
        display.clearDisplay();
        display.setCursor(0,0);
        display.println(status);
        display.display();
    }
    
    void showError(const String &error) {
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("ERROR:");
        display.println(error);
        display.display();
    }
    
    void showText(const String &text) {
        display.clearDisplay();
        display.setCursor(0,0);
        
        // Word wrap implementation
        int16_t x1, y1;
        uint16_t w, h;
        String currentLine;
        String words = text;
        
        while (words.length() > 0) {
            int spaceIndex = words.indexOf(' ');
            String word = (spaceIndex == -1) ? words : words.substring(0, spaceIndex);
            
            display.getTextBounds((currentLine + " " + word).c_str(), 0, 0, &x1, &y1, &w, &h);
            
            if (w > display.width()) {
                display.println(currentLine);
                currentLine = word;
            } else {
                if (currentLine.length() > 0) currentLine += " ";
                currentLine += word;
            }
            
            if (spaceIndex == -1) {
                display.println(currentLine);
                break;
            }
            
            words = words.substring(spaceIndex + 1);
        }
        
        display.display();
    }
    
    void showBatteryWarning() {
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Low Battery!");
        display.display();
    }
    
    void toggleDisplay() {
        displayOn = !displayOn;
        if (displayOn) {
            display.dim(false);
        } else {
            display.dim(true);
        }
        display.display();
    }
    
private:
    Adafruit_SSD1306 display;
    bool displayOn = true;
};

#endif