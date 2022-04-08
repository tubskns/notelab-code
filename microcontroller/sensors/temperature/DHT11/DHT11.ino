#include "DHT.h" // DHT module library

#define DHTPIN 0 // DHT11's data pin is connected to NodeMCU's GPIO0 (D3)
// #define DHTPIN D5 // DHT11's data pin is connected to WeMos GPIO14 (D5)

#define DHTTYPE DHT11 // DHT type
DHT dht(DHTPIN, DHT11); // instantiate DHT object

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  dht.begin(); // initialize the sensor
}

void loop()
{
  float humidity = dht.readHumidity(); 
  if (!isnan(humidity)) {
    String humidity_str = String(humidity); //convert float to string
    Serial.print("Humidity: " + humidity_str + " %\n");
  } else {
    Serial.println("Humidity reading from DHT11 sensor failed!");
  }

  float temperature = dht.readTemperature(); 
  if (!isnan(temperature))
  {
    String temperature_str = String(temperature); //convert float to string
    Serial.print("Temperature: " + temperature_str + " *C\n");
  } else {
    Serial.println("Temperature reading from DHT11 sensor failed!");
  }
  delay(1000);
}
