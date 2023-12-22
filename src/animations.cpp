#include "animations.hpp"

void Animations::setup()
{
  FastLED.addLeds<LEFT_LED_TYPE, LEFT_LED_PIN, LEFT_LED_COLOR_ORDER>(Animations::leftLeds, LEFT_NUM_LEDS);
  FastLED.addLeds<RIGHT_LED_TYPE, RIGHT_LED_PIN, RIGHT_LED_COLOR_ORDER>(Animations::rightLeds, RIGHT_NUM_LEDS);
  FastLED.addLeds<TAIL_LED_TYPE, TAIL_LED_PIN, TAIL_LED_COLOR_ORDER>(Animations::tailLeds, TAIL_NUM_LEDS);

  // FastLED.setBrightness(50);
  FastLED.setBrightness(255);

  policeAnimation.setup(&this->leftLeds, &this->rightLeds, &this->tailLeds);
  emptyAnimation.setup(&this->leftLeds, &this->rightLeds, &this->tailLeds);

  xTaskCreate(
      Animations::showFastLedTaskStatic,
      "showFastLedTask",
      10000,
      this,
      1,
      &this->animationTickTaskHandle);

  xTaskCreate(
      this->animationTickTaskStatic,
      "animationTickTask",
      1000,
      this,
      1,
      &this->showFastLedTaskHandle);
}

void Animations::showFastLedTaskStatic(void *parameters)
{
  // Cast the void* to Animations*
  Animations *animations = static_cast<Animations *>(parameters);
  // Call the non-static method
  animations->showFastLedTask();
}

void Animations::animationTickTaskStatic(void *parameters)
{
  // Cast the void* to Animations*
  Animations *animations = static_cast<Animations *>(parameters);
  // Call the non-static method
  animations->animationTickTask();
}

void Animations::showFastLedTask()
{
  for (;;)
  {
    FastLED.show();
    delay(1000 / LED_FPS);
  }
}

void Animations::animationTickTask()
{
  for (;;)
  {
    if (this->ledState)
    {
      policeAnimation.tick();
    }
    else
    {
      emptyAnimation.tick();
    }
  }
}

void Animations::setLedState(bool ledState)
{
  this->ledState = ledState;
}