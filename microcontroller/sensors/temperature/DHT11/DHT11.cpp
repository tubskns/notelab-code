#include "DHT11.h"
#include "DHT.h" // DHT module library


DHT11::DHT11(DHT dht)
{    
    dht.begin(); // initialize the sensor
    _dht = dht;
}

// function for reading DHT11 sensor data
float DHT11::get_humidity()
{
    float humidity = _dht.readHumidity(); // read humidity (percentage)
    if (isnan(humidity))
    {
        Serial.println("Humidity reading from DHT11 sensor failed!");
        return 0;
    }

    return humidity;
}

float DHT11::get_temperature()
{
    float temperature = _dht.readTemperature(); // read temperature (Celsius by default)
    if (isnan(temperature))
    {
        Serial.println("Temperature reading from DHT11 sensor failed!");
        return 0;
    }
    return temperature;
}
