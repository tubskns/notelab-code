#include "mqtt_client.h"
#include <MQTT.h>
#include <ESP8266WiFi.h>

WiFiClient wifi_client;
MQTTClient mqtt_client;
String _msg;
String _topic;

void callback(String &topic, String &payload){
  Serial.println("Message arrived [" + topic + "]: " + payload);
  _msg = payload;
  _topic = topic;
}

void connect(const char *client_id, String *topics, int num_topics){
  Serial.print("Connecting to MQTT broker... ");
  while (!mqtt_client.connect(client_id, "public", "public")){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("done!");
  for (int i = 0; i < num_topics; i++) {
    mqtt_client.onMessage(callback);
    mqtt_client.subscribe(topics[i]);
    Serial.println("Subscribed to topic: " + topics[i]);
  }
}

void initialize_client(const char *mqtt_broker_ip, const int mqtt_broker_port){
  mqtt_client.begin(mqtt_broker_ip, wifi_client);
}

void publish_message(char *topic, char *msg){
  mqtt_client.publish(topic, msg);
  Serial.println("Message published [ " + String(topic) + " ]: " + String(msg));
}

void check_connection(const char *client_id, String *topics, int num_topics){
  mqtt_client.loop();
  delay(10);
  if (!mqtt_client.connected()) connect(client_id, topics, num_topics);
}

String get_msg(){ return _msg; }

String get_topic(){ return _topic; }

void reset_msg(){
  _msg = "";
  _topic = "";
}
