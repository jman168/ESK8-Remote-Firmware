#include "Board.h"

unsigned char BOARD_ADDRESS[] = {0xCC, 0x50, 0xE3, 0x3C, 0xA8, 0x89};

struct board_status_packet_t {
    float speed;
    float battery;
};

struct board_control_packet_t {
    float throttle;
};

float board_throttle;
float board_speed;
float board_battery;

unsigned long board_last_transmit;

board_status_packet_t rx_packet;
board_control_packet_t tx_packet;

void board_on_data(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&rx_packet, incomingData, sizeof(rx_packet));
    board_battery = rx_packet.battery;
    board_speed = rx_packet.speed;
}

void board_init() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        while(true) {};
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(BOARD_ADDRESS, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_recv_cb(board_on_data);
}

void board_update() {
    unsigned long time = millis();

    if(time-board_last_transmit > 20) {
        tx_packet.throttle = board_throttle;
        esp_now_send(BOARD_ADDRESS, (uint8_t *)&tx_packet, sizeof(tx_packet));
        board_last_transmit = time;
    }
}

void board_set_throttle(float throttle) {
    board_throttle = throttle;
}

float board_get_speed() {
    return board_speed;
}

float board_get_battery() {
    return board_battery;
}