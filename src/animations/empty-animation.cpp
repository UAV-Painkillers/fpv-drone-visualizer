#include "empty-animation.hpp"

void EmptyAnimation::setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds)
{
  this->leftLeds = leftLeds;
  this->rightLeds = rightLeds;
  this->tailLeds = tailLeds;
}

void EmptyAnimation::tick()
{
  tailLeds->fill_solid(CRGB::Black);
  leftLeds->fill_solid(CRGB::Black);
  rightLeds->fill_solid(CRGB::Black);

  delay(1000);
}
