#include "interface_PIR.h"
#include <Arduino.h>

const int pirSensor = 13; // PIR's pin is connected to NodeMCU's GPIO13 (D7) or WeMos GPIO13 (D7)

void initialize_sensor()
{
  pinMode(pirSensor, INPUT); // set sensor pin as input:
}

bool detect_motion()
{
  int pinState = digitalRead(pirSensor); // read the digital value of output pin
  if (pinState == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}
