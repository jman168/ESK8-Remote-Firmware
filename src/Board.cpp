#include "Board.h"

unsigned char BOARD_ADDRESS[] = {0xCC, 0x50, 0xE3, 0x3C, 0xA8, 0x89};

struct board_status_packet_t {
    float speed;
    float battery;
    uint8_t motor_temp;
    bool connection;
};

struct board_control_packet_t {
    float throttle;
};

float board_throttle;
float board_speed;
float board_battery;
uint8_t board_motor_temp;
bool board_connection_status = false;

unsigned long board_last_transmit = 0;
unsigned long board_last_receive = 0;

board_status_packet_t board_rx_packet;
board_control_packet_t board_tx_packet;

void board_on_data(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    board_last_receive = millis();
    memcpy(&board_rx_packet, incomingData, sizeof(board_rx_packet));
    board_battery = board_rx_packet.battery;
    board_speed = board_rx_packet.speed;
    board_motor_temp = board_rx_packet.motor_temp;
    board_connection_status = board_rx_packet.connection;
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
        board_tx_packet.throttle = board_throttle;
        esp_now_send(BOARD_ADDRESS, (uint8_t *)&board_tx_packet, sizeof(board_tx_packet));
        board_last_transmit = time;
    }
}

void board_set_throttle(float throttle) {
    board_throttle = throttle;
}

float board_get_speed() {
    return (board_is_connected())? board_speed: 0.0;
}

float board_get_battery() {
    return (board_is_connected())? board_battery: 0.0;
}

uint8_t board_get_motor_temperature() {
    return (board_is_connected())? board_motor_temp: 0;
}

bool board_is_connected() {
    return (millis() - board_last_receive < 250) && (board_connection_status);
}