#include "interface_DHT11.h"

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  initialize_sensor();
}

void loop()
{
  float humidity = get_humidity();
  String humidity_str = String(humidity); //convert float to string
  Serial.print("Humidity: " + humidity_str + " %\n");

  float temperature = get_temperature();
  String temperature_str = String(temperature); //convert float to string
  Serial.print("Temperature: " + temperature_str + " *C\n");

  delay(1000);
}
