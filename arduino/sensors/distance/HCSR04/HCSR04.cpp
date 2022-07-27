#include "HCSR04.h"
#include <Arduino.h>


HCSR04::HCSR04(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT); // set the trigger pin as output
  pinMode(echoPin, INPUT);  // set the echo pin as input
  _trigPin = trigPin;
  _echoPin = echoPin;
}

float HCSR04::calculate_distance()
{
  // write a pulse: when trigger pin is set to HIGH, start transmitting
  digitalWrite(_trigPin, LOW); // clear the trigger pin
  delayMicroseconds(10);
  digitalWrite(_trigPin, HIGH); //set the trigger pin to HIGH for 10 ms
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  long duration = pulseIn(_echoPin, HIGH); // time elapsed for sending and receiving pulse wave
  float distance = duration * 0.034 / 2;    // calculate distance in cm

  return distance; //return distance
}
