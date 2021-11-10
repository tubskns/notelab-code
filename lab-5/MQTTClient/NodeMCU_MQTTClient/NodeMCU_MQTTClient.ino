#include <ESP8266WiFi.h> // wifi module library 
#include <PubSubClient.h> // MQTT client library

//WiFi parameters
String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 
WiFiClient espClient;

//MQTT parameters 
const char* mqttBroker = "192.168.1.3"; // broker IP address
const int mqttPort =1883; // MQTT port (default :1883)
PubSubClient mqttClient(espClient); // create an instance of MQTT client

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  ConnectoToWiFi(); // connect to the network
  mqttClient.setServer(mqttBroker,mqttPort); // specify the address and the port of the MQTT broker
  mqttClient.setCallback(ReceivedMessage); //handle incoming MQTT messages
  // check when request is accepted by the broker
  while (!mqttClient.connected()) {
  Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP8266 Client")) {
     Serial.println("Connection to MQTT broker established");
    } else {
     Serial.print("failed with state rc=");
     Serial.print(mqttClient.state());
     Serial.println(" Try again in 5 seconds");
     delay(5000);  // wait 5 s before retrying to connect
    }
  }
mqttClient.subscribe("TestTopic"); // subscribe to the topic
mqttClient.publish("TestTopic", "Hello"); // publish to the topic
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
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for(int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void loop() {
 mqttClient.loop();
}
