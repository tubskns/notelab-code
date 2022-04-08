#include "PIR.h"

const int pirSensor = 13; // PIR's pin is connected to NodeMCU's GPIO13 (D7) or WeMos GPIO13 (D7)
PIR pir(pirSensor);

void setup()
{
  Serial.begin(115200);
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
