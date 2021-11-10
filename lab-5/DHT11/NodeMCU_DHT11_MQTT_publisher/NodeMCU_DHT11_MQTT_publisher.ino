#include <ESP8266WiFi.h> // wifi module library 
#include <PubSubClient.h> // MQTT client library
#include "DHT.h" // DHT module library 

//WiFi parameters
String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 
WiFiClient espClient1;

//MQTT parameters 
const char* mqttBroker = "192.168.1.3"; // broker IP address
const int mqttPort =1883; // MQTT port (default :1883)
const char* topic="notelab/dhtsensor/temperatureAndHumidity";
PubSubClient mqttClient(espClient1); // create an instance of MQTT client

//Sensor parameters
#define DHTPIN 0 // DHT11's data pin is connected to NodeMCU's GPIO 0 (D3)
#define DHTTYPE DHT11 // DHT type
DHT dht(DHTPIN, DHT11); // instantiate DHT object 
unsigned long previousSend = 0; // storing last time DHT was updated

const char* id = "microcontroller1"; // identifier

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  ConnectoToWiFi(); // connect to the network
  dht.begin(); // initialize the sensor
  delay(100);
  mqttClient.setServer(mqttBroker,mqttPort); // specify the address and the port of the MQTT broker 
}

void ConnectoToWiFi() {
  Serial.println("Trying to connect to " + ssid);
  WiFi.begin(ssid,pass); // connect to WiFi
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); // add delay until network connected 
    Serial.print(".");
  }  
  Serial.print("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());
}

// function for reading DHT11 sensor data
void getDht11SensorData() { 
  float t = dht.readTemperature(); // read temperature (Celsius by default)
  float h = dht.readHumidity(); // read humidity (percentage)
  if (isnan(h) || isnan(t)) {
   Serial.println("Failed DHT11 sensor reading");
   return;
  }
  String temperature = String(t); //convert float to string
  String humidity = String(h); //convert float to string
  Serial.print("Temperature: " + temperature  + " *C\n");
  Serial.print("Humidity: " + humidity + " %\n");

  // Debug messages
  Serial.print( "Sending temperature and humidity : [" );
  Serial.print( temperature ); Serial.print( "," );
  Serial.print( humidity );
  Serial.print( "]   -> " );
 
  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"id\":\"";
  payload += id;
  payload += "\",";
  payload += "\"temperature\":";
  payload += temperature;
  payload += "\",";
  payload += "\"humidity\":";
  payload += humidity;
  payload += "}";

   // Send payload
   char attributes[100];
   payload.toCharArray(attributes, 100 );
   mqttClient.publish(topic, attributes );
   Serial.println(attributes);
}

// function for checking when request is accepted by the broker
void reconnect() {  
  while (!mqttClient.connected()) { 
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("microcontroller1")) {
      Serial.println("Connection to MQTT broker established");   
    } else {
      Serial.print("failed with state rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Try again in 5 seconds");
      delay(5000);  // wait 5 s before retrying to connect
    }
  }
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  if (millis() - previousSend > 5000) { // update and send sensor data only after 5 s
    getDht11SensorData();
    previousSend = millis();
  }
   mqttClient.loop();  
}
