#include "motion_detection_PIR.h"

void setup()
{
  Serial.begin(115200);
  initialize_sensor();
}

void loop()
{
  bool is_motion = detect_motion();
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
