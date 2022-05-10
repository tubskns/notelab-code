#include "MqttClient.h"
#include <MQTT.h>
#include <ESP8266WiFi.h>

MqttClient::MqttClient(WiFiClient wifi_client, const char *mqtt_broker_ip, const int mqtt_broker_port)
{
  _mqtt_client.begin(mqtt_broker_ip, wifi_client);
}

void callback(String &topic, String &payload)
{
  Serial.println("Message arrived [" + topic + "]: " + payload);
  _msg = payload;
  _topic = topic;
}

void MqttClient::connect(const char *client_id, String *topics, int num_topics)
{
  Serial.print("Connecting to MQTT broker... ");
  while (!_mqtt_client.connect(client_id, "public", "public"))
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("done!");
  for (int i = 0; i < num_topics; i++)
  {
    _mqtt_client.onMessage(callback);
    _mqtt_client.subscribe(topics[i]);
    Serial.println("Subscribed to topic: " + topics[i]);
  }
}

void MqttClient::publish_message(char *topic, char *msg)
{
  _mqtt_client.publish(topic, msg);
  Serial.println("Message published [ " + String(topic) + " ]: " + String(msg));
}

void MqttClient::check_connection(const char *client_id, String *topics, int num_topics)
{
  _mqtt_client.loop();
  delay(10);
  if (!_mqtt_client.connected())
    connect(client_id, topics, num_topics);
}

String MqttClient::get_msg() { return _msg; }

String MqttClient::get_topic() { return _topic; }

void MqttClient::reset_msg()
{
  _msg = "";
  _topic = "";
}
