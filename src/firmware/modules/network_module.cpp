#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class NetworkModule {
public:
    bool connect(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);
        
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 20) {
            delay(500);
            attempts++;
        }
        
        return WiFi.status() == WL_CONNECTED;
    }
    
    void maintain() {
        if (WiFi.status() != WL_CONNECTED) {
            reconnectAttempts++;
            if (reconnectAttempts >= MAX_RECONNECT_ATTEMPTS) {
                ESP.restart();
            }
        } else {
            reconnectAttempts = 0;
        }
    }
    
    String sendCommand(const String &command) {
        if (WiFi.status() != WL_CONNECTED) {
            return "Network Error";
        }
        
        HTTPClient http;
        
        // Create JSON payload
        StaticJsonDocument<200> doc;
        doc["command"] = command;
        String jsonString;
        serializeJson(doc, jsonString);
        
        // Send POST request
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");
        
        int httpResponseCode = http.POST(jsonString);
        String response = "Error";
        
        if (httpResponseCode > 0) {
            response = http.getString();
            
            // Parse JSON response
            StaticJsonDocument<200> responseDoc;
            DeserializationError error = deserializeJson(responseDoc, response);
            
            if (!error) {
                response = responseDoc["response"].as<String>();
            }
        }
        
        http.end();
        return response;
    }
    
    bool sendAudio(const uint8_t* audioData, size_t length) {
        if (WiFi.status() != WL_CONNECTED) {
            return false;
        }
        
        HTTPClient http;
        http.begin(serverUrl + "/audio");
        http.addHeader("Content-Type", "application/octet-stream");
        
        int httpResponseCode = http.POST(audioData, length);
        http.end();
        
        return httpResponseCode == 200;
    }
    
    void setServer(const String &url) {
        serverUrl = url;
    }
    
private:
    String serverUrl = "http://192.168.1.100:8000";
    const int MAX_RECONNECT_ATTEMPTS = 5;
    int reconnectAttempts = 0;
};

#endif
