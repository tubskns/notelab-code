#include <ESP8266WiFi.h> // wifi module library 
#include <PubSubClient.h> // MQTT client library 

//WiFi parameters
String ssid = "netw1"; // student's network SSID
String pass = "password1"; //student's network password 
WiFiClient espClient1;

//MQTT parameters 
const char* mqttBroker = "192.168.1.3"; // broker IP address
const int mqttPort =1883; // MQTT port (default :1883)
const char* topic="notelab/pir/motion";
PubSubClient mqttClient(espClient1); // create an instance of MQTT client

//Sensor parameters
const int pirSensor = 13; // PIR's pin is connected to NodeMCU's GPIO 13 (D7)
int calibrationTime=30; //time for sensor to calibrate
int pinState = 0; // store pin status 
unsigned long previousSend = 0; // storing last time PIR was updated

const char* id = "microcontroller1"; // identifier

void setup() {
  Serial.begin(115200); // establish serial communication at baud rate 115200
  pinMode(pirSensor, INPUT); // set sensor pin as input:
  Serial.print("Calibrating sensor ");
  for (int i=0; i<calibrationTime; i++){ // give some time to calibrate
    Serial.print(".");
    delay(100);
  }
  Serial.println("Sensor active");
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

// function for reading PIR data
void getMotionData() { 
  pinState = digitalRead(pirSensor); // read the digital value of output pin  
  String motion="off";
  if (pinState == HIGH) {
    motion="detected";
   }
  else {
    motion="absent";
  }
   
  // Debug messages
  Serial.print( "Sending motion data -> " );
  
  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"id\":\"";
  payload += id;
  payload += "\",";
  payload += "\"motion\":";
  payload += motion;
  payload += "}";
  
  // Send payload
  char attributes[100];
  payload.toCharArray(attributes, 100 );
  mqttClient.publish(topic, attributes );
  Serial.println(attributes); 
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  if (millis() - previousSend > 1000) { // update and send sensor data only after 1 s
    getMotionData();
    previousSend = millis();
  }
   mqttClient.loop();  
}
