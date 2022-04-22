const int buzzer = 9;

void setup()
{
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  tone(buzzer, 1000); // 1KHz sound signal
  delay(1000);
  noTone(buzzer); // stop sound
  delay(1000);
}