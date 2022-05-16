#define LED D13 // Arduino UNO WiFi Rev2's builtin LED is at pin GPIO16 (D13)

void setup()
{
    pinMode(LED, OUTPUT); // LED pin as output.
}

void loop()
{
    digitalWrite(LED, HIGH); // turn the LED off
    delay(1000);             // wait for 1 second
    digitalWrite(LED, LOW);  // turn the LED on
    delay(1000);             // wait for 1 second
}