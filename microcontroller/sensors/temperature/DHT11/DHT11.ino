#include "DHT11.h"
#include "DHT.h" // DHT module library

#define DHTTYPE DHT_TYPE // DHT type
#define DHTPIN 0 // DHT11's data pin is connected to NodeMCU's GPIO0 (D3)
// #define DHTPIN D5 // DHT11's data pin is connected to WeMos GPIO14 (D5)

DHT dht(DHTPIN, DHT_TYPE); // instantiate DHT object
DHT11 dht11(dht);

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
}

void loop()
{
  float humidity = dht11.get_humidity();
  String humidity_str = String(humidity); //convert float to string
  Serial.print("Humidity: " + humidity_str + " %\n");

  float temperature = dht11.get_temperature();
  String temperature_str = String(temperature); //convert float to string
  Serial.print("Temperature: " + temperature_str + " *C\n");

  delay(1000);
}
