#include "ultrasonic_distance_HCSR04.h"

const int trigPin = 5; // HC-SR04's trigger pin is connected to NodeMCU's GPIO 5 (D1)
const int echoPin = 4; // HC-SR04's echo pin is connected to NodeMCU's GPIO 4 (D2)

// const int trigPin = D4; // HC-SR04's trigger pin is connected to WeMos GPIO 4 (D4)
// const int echoPin = D5; // HC-SR04's echo pin is connected to WeMos GPIO 14 (D5)

void initialize_sensor()
{
  pinMode(trigPin, OUTPUT); // set the trigger pin as output
  pinMode(echoPin, INPUT);  // set the echo pin as input
}

int calculate_distance()
{
  // write a pulse: when trigger pin is set to HIGH, stary transmitting
  digitalWrite(trigPin, LOW); // clear the trigger pin
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH); //set the trigger pin to HIGH for 10 ms
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH); // time elapsed for sending and receiving pulse wave
  int distance = duration * 0.034 / 2;    // calculate distance in cm

  return distance; //return distance
}