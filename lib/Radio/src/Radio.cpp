#include <Constants.h>
#include <Arduino.h>
#include <Radio.h>

#include <esp_now.h>
#include <WiFi.h>

Radio::Radio(){
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    // callback when data is sent
    /*void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
        Serial.print("\r\nLast Packet Send Status:\t");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    }*/

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);
    
    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
}

bool Radio::send_data(byte* packet, byte packet_size){
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &packet, sizeof(packet));
    
    if (result == ESP_OK) {
        Serial.println("Sent with success");
        return true;
    }
    else {
        Serial.println("Error sending the data");
        return false;
    }
}

// Define the callback function outside the class
void Radio::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


 
