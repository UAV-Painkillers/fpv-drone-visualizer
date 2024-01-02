#include "color-blink-animation.hpp"

void ColorBlinkAnimation::setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds)
{
    this->leftLeds = leftLeds;
    this->rightLeds = rightLeds;
    this->tailLeds = tailLeds;
}

void ColorBlinkAnimation::tick()
{
    switch (this->step)
    {
    case 0:
        this->leftLeds->fill_solid(CRGB::Red);
        this->rightLeds->fill_solid(CRGB::Red);
        this->tailLeds->fill_solid(CRGB::Red);
        break;

    case 1:
        this->leftLeds->fill_solid(CRGB::Green);
        this->rightLeds->fill_solid(CRGB::Green);
        this->tailLeds->fill_solid(CRGB::Green);
        break;

    case 2:
        this->leftLeds->fill_solid(CRGB::Blue);
        this->rightLeds->fill_solid(CRGB::Blue);
        this->tailLeds->fill_solid(CRGB::Blue);
        break;

    default:
        this->leftLeds->fill_solid(CRGB::White);
        this->rightLeds->fill_solid(CRGB::White);
        this->tailLeds->fill_solid(CRGB::White);
        break;
    }

    this->step++;

    if (this->step > 3)
    {
        this->step = 0;
    }

    delay(500);
}
