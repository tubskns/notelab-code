#include "MqttClient.h"
#include "WifiClient.h"
#include "HCSR04.h"
#include "PIR.h"
#include "DHT.h"
#include <ArduinoJson.h>

char *ssid_wifi = "netw0";     
char *pass_wifi = "password1";

const char *mqtt_broker_ip = "RPi_IP";
const int mqtt_broker_port = 1883;
const char* client_id = "publisher_sensors";
char* temp_topic = "temp_topic";
char* dist_topic = "dist_topic";
char* motion_topic = "motion_topic";
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port);

#define DHTPIN 3 //specify DHT11's pin
#define DHTTYPE DHT11 // DHT11's type
DHT dht(DHTPIN, DHT11);
HCSR04 hcsr04(1, 2); // specify HC-SR04 trig and echo pins
PIR pir(7); // specify PIR's pin

DynamicJsonDocument temp_doc(1024), dist_doc(1024), motion_doc(1024);

void setup(){
  Serial.begin(9600); 
  wifi_client.connect();
  mqtt_client.connect(client_id);
  dht.begin(); // initialize the sensor
}

void loop(){
  mqtt_client.check_connection(client_id);
  float temperature = dht.readTemperature(); 
  if (!isnan(temperature)){
    temp_doc["id"] = client_id;
    temp_doc["temperature"] = temperature;
  } 
  float distance = hcsr04.calculate_distance();
  dist_doc["id"] = client_id, dist_doc["distance"] = distance;
  bool is_motion = pir.detect_motion();
  motion_doc["id"] = client_id, motion_doc["motion"] = is_motion;
  char temp_out[500], dist_out[500], motion_out[500];
  serializeJson(temp_doc, temp_out);
  serializeJson(dist_doc, dist_out);
  serializeJson(motion_doc, motion_out);
  mqtt_client.publish_message(temp_topic, temp_out);
  mqtt_client.publish_message(dist_topic, dist_out);
  mqtt_client.publish_message(motion_topic, motion_out);
}
