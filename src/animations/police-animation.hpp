#pragma once

#include "animation-interface.hpp"

class PoliceAnimation: public IAnimation {
    public:
        void setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds) override;
        void tick() override;

    private:
        void blinkArm(LedArm arm);
        void resetArm(LedArm arm);
};
