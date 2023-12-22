#include "police-animation.hpp"

bool flashSideFlag = false;
const int blinkSpacing = 500;

void PoliceAnimation::setup(CRGBArray<LEFT_NUM_LEDS> *leftLeds, CRGBArray<RIGHT_NUM_LEDS> *rightLeds, CRGBArray<TAIL_NUM_LEDS> *tailLeds)
{
  this->leftLeds = leftLeds;
  this->rightLeds = rightLeds;
  this->tailLeds = tailLeds;
}

void PoliceAnimation::blinkArm(LedArm arm)
{
  const int blinkOnTime = 50;
  bool isOn = false;

  for (int blinkCount = 0; blinkCount <= 8; blinkCount++)
  {
    switch (arm)
    {
    case LED_LEFT_ARM:
      leftLeds->fill_solid(CRGB::Red);
      if (!isOn)
      {
        leftLeds->fadeToBlackBy(150);
      }
      break;

    case LED_RIGHT_ARM:
      rightLeds->fill_solid(CRGB::Blue);
      if (!isOn)
      {
        rightLeds->fadeToBlackBy(150);
      }
      break;

    case LED_TAIL_ARM:
      tailLeds->fill_solid(CRGB::White);
      if (!isOn)
      {
        tailLeds->fadeToBlackBy(150);
      }
      break;
    }

    delay(blinkOnTime);

    isOn = !isOn;
  }
}

void PoliceAnimation::resetArm(LedArm arm)
{
  switch(arm) {
    case LED_LEFT_ARM:
      leftLeds->fill_solid(CRGB::Red);
      leftLeds->fadeToBlackBy(150);
      break;

    case LED_RIGHT_ARM:
      rightLeds->fill_solid(CRGB::Blue);
      rightLeds->fadeToBlackBy(150);
      break;

    case LED_TAIL_ARM:
      tailLeds->fill_solid(CRGB::White);
      tailLeds->fadeToBlackBy(150);
      break;
  }
}

void PoliceAnimation::tick()
{
  tailLeds->fill_solid(CRGB::White);
  tailLeds->fadeToBlackBy(150);

  resetArm(LED_LEFT_ARM);
  resetArm(LED_RIGHT_ARM);

  delay(blinkSpacing);

  blinkArm(LED_LEFT_ARM);
  resetArm(LED_RIGHT_ARM);

  blinkArm(LED_RIGHT_ARM);
  resetArm(LED_RIGHT_ARM);

  flashSideFlag = !flashSideFlag;
}
