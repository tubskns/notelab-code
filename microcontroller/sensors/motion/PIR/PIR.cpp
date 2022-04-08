#include "PIR.h"
#include <Arduino.h>


PIR::PIR(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

bool PIR::detect_motion()
{
  int pinState = digitalRead(_pin);
  if (pinState == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}
