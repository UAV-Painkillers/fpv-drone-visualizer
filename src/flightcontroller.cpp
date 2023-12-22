#include "flightcontroller.hpp"

void Flightcontroller::setup(/*HardwareSerial *fcSerial*/)
{
  // this->fcSerial = fcSerial;
  pinMode(FC_LED_PINIO_PIN, INPUT);
}

void Flightcontroller::onArmingStateChange(bool_state_callback_t callback)
{
  Flightcontroller::armingStateCallback = callback;
}

void Flightcontroller::onLedStateChange(bool_state_callback_t callback)
{
  Flightcontroller::ledStateCallback = callback;
}

void Flightcontroller::checkLedPin()
{
  if (this->ledStateCallback != NULL || this->ledStateCallback != nullptr)
  {
    Serial.println("Processing LED state change");
    bool newLedState = digitalRead(FC_LED_PINIO_PIN);
    if (newLedState != this->ledState)
    {
      Serial.print("LED state changed to ");
      Serial.println(newLedState ? "on" : "off");
      this->ledState = newLedState;
      this->ledStateCallback(this->ledState);
    }
  }
}

void Flightcontroller::loop()
{
  EVERY_N_MILLISECONDS(25) {
    this->checkLedPin();
  }

  // ltm_loop(*this->fcSerial);

  /*
  if (this->armingStateCallback != NULL && this->armingStateCallback != nullptr)
  {
    Serial.println("Processing arming state change");

    bool newArmState = LTM_DATA.armed;
    if (newArmState != this->armState)
    {
      Serial.print("Arming state changed to ");
      Serial.println(newArmState ? "armed" : "disarmed");
      this->armState = newArmState;
      this->armingStateCallback(this->armState);
    }
  }
  */
}