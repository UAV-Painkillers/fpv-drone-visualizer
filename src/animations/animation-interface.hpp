#pragma once

#include <FastLED.h>
#include "const.h"

enum LedArm {
    LED_LEFT_ARM = 0,
    LED_RIGHT_ARM = 1,
    LED_TAIL_ARM = 2
};

class IAnimation
{
public:
    virtual void setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds) = 0;
    virtual void tick() = 0;

protected:
    CRGBArray<LEFT_NUM_LEDS> *leftLeds;
    CRGBArray<RIGHT_NUM_LEDS> *rightLeds;
    CRGBArray<TAIL_NUM_LEDS> *tailLeds;
};