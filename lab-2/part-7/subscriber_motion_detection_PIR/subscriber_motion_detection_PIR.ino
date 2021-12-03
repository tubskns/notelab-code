#include <ESP8266WiFi.h> // wifi module library 
#include <PubSubClient.h> // MQTT client library

//WiFi parameters
String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 
WiFiClient espClient2;

//MQTT parameters 
const char* mqttBroker = "192.168.1.3"; // broker IP address
const int mqttPort =1883; // MQTT port (default :1883)
const char* topic="notelab/pir/motion";
PubSubClient mqttClient(espClient2); // create an instance of MQTT client

#define LED D1 //external LED is connected to NodeMCU's pin GPIO5 (D1)
const char* id = "microcontroller2"; // identifier

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  pinMode(LED, OUTPUT); // initialize LED as an output
  ConnectoToWiFi(); // connect to the network
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

// client receives message from broker
void ReceivedMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message:");
  String message;
  for(int i = 0; i < length; i++) {
    message=message +(char)payload[i];
  }
  Serial.println(message);
  //add a condition for turning on a LED
  if (message[34]=='d') {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

// function for checking when request is accepted by the broker
void reconnect() {  
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("microcontroller2")) {
      Serial.println("Connection to MQTT broker established");
      mqttClient.subscribe(topic); //subscribe to topic   
      mqttClient.setCallback(ReceivedMessage);
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
    Serial.println(mqttClient.state());
    reconnect();
    Serial.print("Message received in topic: ");
    Serial.println(topic);
    mqttClient.setCallback(ReceivedMessage);
  } 
  mqttClient.loop();

}
