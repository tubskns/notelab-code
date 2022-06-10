#include "HCSR04.h"

const int trigPin = 1; // HC-SR04's trigger pin is connected to board's digital pin 1
const int echoPin = 2; // HC-SR04's echo pin is connected to board's digital pin 2

HCSR04 hcsr04(trigPin, echoPin);

void setup()
{
    Serial.begin(9600); // Serial.begin(115200);
}

void loop()
{
    float distance = hcsr04.calculate_distance();
    String distance_str = String(distance); // convert int to string
    Serial.print("Distance: " + distance_str + " cm\n");
    delay(1000);
}
