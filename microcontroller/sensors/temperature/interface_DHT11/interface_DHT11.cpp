#include "interface_DHT11.h"
#include "DHT.h" // DHT module library

#define DHTPIN 0 // DHT11's data pin is connected to NodeMCU's GPIO 0 (D3)
// #define DHTPIN D5 // DHT11's data pin is connected to WeMos GPIO 14 (D5)
#define DHTTYPE DHT11 // DHT type

DHT dht(DHTPIN, DHT11); // instantiate DHT object

void initialize_sensor()
{
    dht.begin(); // initialize the sensor
}

// function for reading DHT11 sensor data
float get_humidity()
{
    float humidity = dht.readHumidity(); // read humidity (percentage)
    if (isnan(humidity))
    {
        Serial.println("Humidity reading from DHT11 sensor failed!");
        return 0;
    }

    return humidity;
}

float get_temperature()
{
    float temperature = dht.readTemperature(); // read temperature (Celsius by default)
    if (isnan(temperature))
    {
        Serial.println("Temperature reading from DHT11 sensor failed!");
        return 0;
    }
    return temperature;
}
