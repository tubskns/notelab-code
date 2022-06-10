#include "PIR.h"

const int pirSensor = 7; // PIR's pin is connected to to board's digital pin 7
PIR pir(pirSensor);

void setup()
{
  Serial.begin(9600); // Serial.begin(115200);
}

void loop()
{
  bool is_motion = pir.detect_motion();
  if (is_motion == true)
  {
    Serial.println("Motion detected!");
  }
  else
  {
    Serial.println("Motion absent!");
  }
  delay(1000);
}
