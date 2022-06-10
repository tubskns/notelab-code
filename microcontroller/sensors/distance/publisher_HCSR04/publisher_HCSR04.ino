#include "MqttClient.h"
#include "WifiClient.h"
#include "HCSR04.h"
#include <ArduinoJson.h>

char *ssid_wifi = "netw0";     // student's network SSID
char *pass_wifi = "password1"; // student's network password

const char *mqtt_broker_ip = "192.168.1.3";
const int mqtt_broker_port = 1883;
const char *client_id = "publisher_HCSR04";
const char *publish_topic = "distance_topic";
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port);

const int trigPin = 1; // HC-SR04's trigger pin is connected to board's digital pin 1
const int echoPin = 2; // HC-SR04's echo pin is connected to board's digital pin 2

HCSR04 hcsr04(trigPin, echoPin);

void setup()
{
  Serial.begin(9600); // Serial.begin(115200);
  wifi_client.connect();
  mqtt_client.connect(client_id);
}

void loop()
{
  mqtt_client.check_connection(client_id);
  int distance = hcsr04.calculate_distance();
  String distance_str = String(distance); // convert int to string
  Serial.print("Distance: " + distance_str + " cm\n");
  delay(1000);
  
  DynamicJsonDocument doc(1024);

  doc["id"] = "publisher_HCSR04";
  doc["distance"] = distance;
  // Generate the prettified JSON and send it to the Serial port
  // serializeJsonPretty(doc, Serial);

  String json_doc;
  serializeJson(doc, json_doc);

  char buf[500];
  json_doc.toCharArray(buf, 500);
  mqtt_client.publish_message(publish_topic, buf);
  delay(5000);
}
