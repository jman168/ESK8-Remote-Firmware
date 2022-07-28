#include "Board.h"

Board::Board() {
    _radio = new RF24(7,8);

    if(!_radio->begin()) {
        Serial.println("Radio hardware is not responding!!");
    }

    _radio->setPALevel(RF24_PA_HIGH);

    _radio->enableDynamicPayloads();

    _radio->enableAckPayload();

    _radio->openWritingPipe((const uint8_t*)&_boardAddr);
    _radio->openReadingPipe(1, (const uint8_t*)&_remoteAddr);

    _radio->stopListening();

    _radio->printPrettyDetails();
}

void Board::handle() {
    unsigned long time = millis();

    if(time-_lastTransmit > 20) {
        ControlPacket txPacket;
        txPacket.throttle = _throttle;
        bool ret = _radio->write(&txPacket, sizeof(txPacket));
        
        uint8_t pipe;
        if(ret) {
            if(_radio->available(&pipe)) {
                AKCPacket ackPacket;
                _radio->read(&ackPacket, sizeof(ackPacket));

                _speed = ackPacket.speed;
                _battery = ackPacket.battery;
            }
        } else {
            Serial.println("Transmission failed or timed out");
        }
    }
}

void Board::setThrottle(float throttle) {
    _throttle = throttle;
}

float Board::getSpeed() {
    return _speed;
}

float Board::getBattery() {
    return _battery;
}