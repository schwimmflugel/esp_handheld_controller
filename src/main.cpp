#include <Arduino.h>
#include <Controls.h>
#include <Radio.h>
#include <Constants.h>

//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

Controls control;
Radio radio;

// Define the callback function outside the class
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


byte data_packet[PACKET_LENGTH];


void setup() {
  Serial.begin(57600);
  Serial.println("Started.");
  radio.begin();
  control.begin();

}

void loop() {
  if( control.run() ){
    control.get_button_data(data_packet);
    radio.send_data(data_packet, PACKET_LENGTH);
  }
}

