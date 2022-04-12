#include "mqtt_client.h"
#include <MQTT.h>
#include <ESP8266WiFi.h>

WiFiClient wifi_client;
MQTTClient mqtt_client;
String _msg;
String _topic;

void connect(const char *client_id){
  Serial.print("\nConnecting to MQTT broker... ");
  while (!mqtt_client.connect(client_id, "public", "public")){
    Serial.print(".");
    delay(1000);
  }
  Serial.print("connected!");
}

void callback(String &topic, String &payload){
  Serial.println("Message arrived [" + topic + "]: " + payload);
  _msg = payload;
  _topic = topic;
}

void initialize_client(const char *mqtt_broker_ip, const int mqtt_broker_port){
  mqtt_client.begin(mqtt_broker_ip, wifi_client);
}

void subscribe_to_topic(char *topics){
  for (int i = 0; i < (sizeof(topic) / sizeof(topic[0])); i++) {
      Serial.println("Subscribing to topic: " + String(topics[i]));
      mqtt_client.onMessage(callback);
      mqtt_client.subscribe(topics[i]);
  }
}

void publish_message(char *topic, char *msg){
  Serial.println("Publishing message [ " + String(topic) + " ]: " + String(msg));
  mqtt_client.publish(topic, msg);
}

void check_connection(const char *client_id){
  mqtt_client.loop();
  delay(10);
  if (!mqtt_client.connected()){ connect(client_id); }
}

String get_msg(){ return _msg; }

String get_topic(){ return _topic; }

void reset_msg(){
  _msg = ""
  _topic = ""
}