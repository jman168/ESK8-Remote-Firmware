#pragma once 

#include <SPI.h>
#include "RF24.h"

struct AKCPacket {
    float speed;
    float battery;
};

struct ControlPacket {
    float throttle;
};

class Board {
    public:
        Board();

        void handle();

        void setThrottle(float throttle);
        float getSpeed();
        float getBattery();

    private:
        RF24 *_radio;

        float _throttle;
        float _speed;
        float _battery;

        unsigned long _lastTransmit = 0;

        const char _boardAddr[6] = "BESK8"; // board address
        const char _remoteAddr[6] = "RESK8"; // remote address
};