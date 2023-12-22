#pragma once

#include "const.h"
#include <functional>

// #include "ltm.hpp"

typedef std::function<void(bool)> bool_state_callback_t;

class Flightcontroller {
    public:
        void setup(/*HardwareSerial *fcSerial*/);
        void loop();
        void onArmingStateChange(bool_state_callback_t callback);
        void onLedStateChange(bool_state_callback_t callback);

    private:
        bool_state_callback_t armingStateCallback;
        bool_state_callback_t ledStateCallback;
        bool armState;
        bool ledState;
        void checkLedPin();
        // HardwareSerial *fcSerial;
};
