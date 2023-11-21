#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <Constants.h>
#include <esp_now.h>
#include <WiFi.h>


class Radio{

    public:
        Radio();
        bool send_data(byte* packet, byte packet_size);


    private:
        esp_now_peer_info_t peerInfo;
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);


};



#endif