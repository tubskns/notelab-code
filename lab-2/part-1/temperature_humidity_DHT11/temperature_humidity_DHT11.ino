#include "DHT.h" // DHT module library

#define DHTPIN 0 // DHT11's data pin is connected to NodeMCU's GPIO 0 (D3)
// #define DHTPIN D5 // DHT11's data pin is connected to WeMos GPIO 14 (D5)
#define DHTTYPE DHT11 // DHT type

DHT dht(DHTPIN, DHT11);         // instantiate DHT object
unsigned long previousSend = 0; // storing last time DHT was updated

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  Serial.println("DHT11 test!");
  Serial.println("Collecting temperature and humidity data:");
  dht.begin(); // initialize the sensor
}

// function for reading DHT11 sensor data
void getDht11SensorData()
{
  float t = dht.readTemperature(); // read temperature (Celsius by default)
  float h = dht.readHumidity();    // read humidity (percentage)
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed DHT11 sensor reading");
    return;
  }
  String temperature = String(t); //convert float to string
  String humidity = String(h);    //convert float to string
  Serial.print("Temperature: " + temperature + " *C\n");
  Serial.print("Humidity: " + humidity + " %\n");
}

void loop()
{
  if (millis() - previousSend > 1000)
  { // update and send sensor data only after 1 s
    getDht11SensorData();
    previousSend = millis();
  }
}
