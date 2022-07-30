#include "Board.h"

struct board_akc_packet_t {
    float speed;
    float battery;
};

struct board_control_packet_t {
    float throttle;
};

RF24 *board_radio;

float board_throttle;
float board_speed;
float board_battery;

unsigned long board_last_transmit;

const char board_board_addr[6] = "BESK8"; // board address
const char board_remote_addr[6] = "RESK8"; // remote address

void board_init() {
    board_radio = new RF24(7,8);

    if(!board_radio->begin()) {
        Serial.println("Radio hardware is not responding!!");
        while(true) {}
    }

    board_radio->setDataRate(RF24_250KBPS);

    board_radio->setChannel(50);

    board_radio->setPALevel(RF24_PA_LOW);

    board_radio->enableDynamicPayloads();

    board_radio->enableAckPayload();

    board_radio->openWritingPipe((const uint8_t*)&board_board_addr);
    board_radio->openReadingPipe(1, (const uint8_t*)&board_remote_addr);

    board_radio->stopListening();

    board_radio->printPrettyDetails();
}

void board_update() {
    unsigned long time = millis();

    if(time-board_last_transmit > 20) {
        board_control_packet_t tx_packet;
        tx_packet.throttle = board_throttle;
        bool ret = board_radio->write(&tx_packet, sizeof(tx_packet));
        board_last_transmit = time;
        
        uint8_t pipe;
        if(ret) {
            if(board_radio->available(&pipe)) {
                board_akc_packet_t ack_packet;
                board_radio->read(&ack_packet, sizeof(ack_packet));

                board_speed = ack_packet.speed;
                board_battery = ack_packet.battery;
            }
        } else {
            Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            board_radio->printPrettyDetails();
        }
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