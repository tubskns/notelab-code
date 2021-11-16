#include "mqtt_client.h"
#include <MQTT.h> // MQTT client library
#include <ESP8266WiFi.h>

WiFiClient wifi_client;
MQTTClient mqtt_client;
const char* client_id;
String buffer;

void connect() {
  Serial.print("\nConnecting to MQTT broker... ");
  while (!mqtt_client.connect(client_id, "public", "public")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("connected!");
}

void callback(String &topic, String &payload) {
  Serial.println("Message arrived [" + topic + "]: " + payload);
  buffer = payload;
}

void initialize_client(const char* mqtt_broker_ip, const int mqtt_broker_port, const char* id)
{
    mqtt_client.begin(mqtt_broker_ip, wifi_client);
    client_id = id;
    connect();
}

void subscribe_to_topic(char* topic){
    Serial.print("Subscribing to topic: ");
    Serial.println(topic);
    mqtt_client.onMessage(callback); //handle incoming MQTT messages
    mqtt_client.subscribe(topic); // subscribe to the topic
}

void publish_message(char* topic, char* msg)
{
    Serial.print("Publishing menssage [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(msg);
    mqtt_client.publish(topic, msg); // publish to the topic
}

void check_connection()
{
  mqtt_client.loop();
  delay(10);

  // check if connected
  if (!mqtt_client.connected()) {
    connect();
  }
}

String get_buffer(){
    return buffer;
}

