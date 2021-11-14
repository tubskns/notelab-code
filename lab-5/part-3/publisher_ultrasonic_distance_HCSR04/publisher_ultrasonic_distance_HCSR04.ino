#include <ESP8266WiFi.h> // wifi module library 
#include <PubSubClient.h> // MQTT client library 

//WiFi parameters
String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 
WiFiClient espClient1;

//MQTT parameters 
const char* mqttBroker = "192.168.1.3"; // broker IP address
const int mqttPort =1883; // MQTT port (default :1883)
const char* topic="notelab/hcsr04/distance";
PubSubClient mqttClient(espClient1); // create an instance of MQTT client

//Sensor parameters
const int trigPin = 5; // HC-SR04's trigger pin is connected to NodeMCU's GPIO 5 (D1)
const int echoPin = 4; // HC-SR04's echo pin is connected to NodeMCU's GPIO 4 (D2)
long duration; // storing time elapsed for sending and receiving pulse wave 
int dist; //storing distance to an object
unsigned long previousSend = 0; // storing last time HCSR04 was updated

const char* id = "microcontroller1"; // identifier

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  pinMode(trigPin, OUTPUT); // set the trigger pin as output
  pinMode(echoPin, INPUT); // set the echo pin as input
  ConnectoToWiFi(); // connect to the network
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

// function for reading HC-SR04 sensor data
void getDistanceData() { 
  // write a pulse: when trigger pin is set to HIGH, stary transmitting
  digitalWrite(trigPin, LOW); // clear the trigger pin
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH); //set the trigger pin to HIGH for 10 ms
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH); // read the echo pin 
  dist=duration*0.034/2; // calculate distance in cm 
  String distance = String (dist); // convert int to string    
  Serial.print("Distance: " + distance + " cm\n");
  
  // Debug messages
  Serial.print( "Sending distance data : [" );
  Serial.print( distance );
  Serial.print( "]   -> " );
  
  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"id\":\"";
  payload += id;
  payload += "\",";
  payload += "\"distance\":";
  payload += distance;
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
    getDistanceData();
    previousSend = millis();
  }
   mqttClient.loop();  
}
