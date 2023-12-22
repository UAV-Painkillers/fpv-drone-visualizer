#pragma once

#include "animation-interface.hpp"

class EmptyAnimation: public IAnimation
{
public:
    void setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds) override;
    void tick() override;
};
