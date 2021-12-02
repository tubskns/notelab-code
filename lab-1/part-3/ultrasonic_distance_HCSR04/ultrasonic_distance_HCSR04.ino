#include "ultrasonic_distance_HCSR04.h"

void setup()
{
    Serial.begin(115200); // establish serial communication at baud rate 115200
    initialize_sensor();
}

void loop()
{
    int distance = calculate_distance();
    String distance_str = String(distance); // convert int to string
    Serial.print("Distance: " + distance_str + " cm\n");
    delay(1000);
}
