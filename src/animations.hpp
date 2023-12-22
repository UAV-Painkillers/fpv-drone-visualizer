#pragma once

#include <FastLED.h>
#include <functional>

#include "const.h"

#include "animations/police-animation.hpp"
#include "animations/empty-animation.hpp"

class Animations {
    public:
        void setup();
        void setLedState(bool ledState);

        static void showFastLedTaskStatic(void* parameters);
        static void animationTickTaskStatic(void* parameters);

        void showFastLedTask();
        void animationTickTask();

    private:
        TaskHandle_t showFastLedTaskHandle;
        TaskHandle_t animationTickTaskHandle;

        CRGBArray<LEFT_NUM_LEDS> leftLeds;
        CRGBArray<RIGHT_NUM_LEDS> rightLeds;
        CRGBArray<TAIL_NUM_LEDS> tailLeds;

        bool ledState = false;

        EmptyAnimation emptyAnimation;
        PoliceAnimation policeAnimation;
};
