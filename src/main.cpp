
#include <Arduino.h>
#include <FastLED.h>

#include "const.h"
#include "flightcontroller.hpp"
#include "animations.hpp"

Animations animations;
Flightcontroller flighcontroller;

void setup()
{
  Serial.begin(LOGGING_BAUD);
  // Serial1.begin(MSP_BAUD_RATE, SERIAL_8N1, FC_RX_PIN, FC_TX_PIN);

  delay(5000);
  Serial.println("Starting up...");
  animations.setup();

  flighcontroller.setup(/*&Serial1*/);

  flighcontroller.onLedStateChange([](bool ledState)
                                 { animations.setLedState(ledState); });
}

void loop()
{
  flighcontroller.loop();
}
