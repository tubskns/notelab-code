#include "HCSR04.h"

const int trigPin = 5; // HC-SR04's trigger pin is connected to NodeMCU's GPIO5 (D1)
const int echoPin = 4; // HC-SR04's echo pin is connected to NodeMCU's GPIO4 (D2)

//const int trigPin = 2; // HC-SR04's trigger pin is connected to WeMos GPIO2 (D4)
//const int echoPin = 14; // HC-SR04's echo pin is connected to WeMos GPIO14 (D5)

HCSR04 hcsr04(trigPin, echoPin);

void setup()
{
    Serial.begin(115200); // establish serial communication at baud rate 115200
}

void loop()
{
    int distance = hcsr04.calculate_distance();
    String distance_str = String(distance); // convert int to string
    Serial.print("Distance: " + distance_str + " cm\n");
    delay(1000);
}
