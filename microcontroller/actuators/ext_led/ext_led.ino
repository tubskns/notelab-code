#define LED D1 // external LED is connected to board's digital pin 1

void setup()
{
    pinMode(LED, OUTPUT); // initialize LED as an output
}

void loop()
{
    digitalWrite(LED, HIGH); // turn the LED off
    delay(1000);             // wait for 1 second
    digitalWrite(LED, LOW);  // turn the LED on
    delay(1000);             // wait for 1 second
}
