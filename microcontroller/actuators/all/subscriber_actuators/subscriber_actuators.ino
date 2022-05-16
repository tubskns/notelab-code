#include "MqttClient.h"
#include "WifiClient.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";
String pass_wifi = "password1";

const char *mqtt_broker_ip = "192.168.1.3";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_sensors";
const int num_subscribe_topics = 3;
String subscribe_topics[num_subscribe_topics] = {"motion_topic", "dist_topic", "temp_topic"};
uint8_t leds[3] = {D1, D2, D3}; // green, yellow, red
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port, subscribe_topics, num_subscribe_topics);

DynamicJsonDocument msg_doc(1024);
float prev_temp = 0;
int led2_state = LOW;
long led2_interval = 1000000;
unsigned long prev_millis = 0;

void setup()
{
  Serial.begin(115200);
  wifi_client.connect();
  mqtt_client.connect(client_id);
  for (int i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++)
    pinMode(leds[i], OUTPUT);
}

void loop()
{ 
  mqtt_client.check_connection(client_id);
  String msg = mqtt_client.get_msg();
  String topic = mqtt_client.get_topic();
  unsigned long current_millis = millis();
  deserializeJson(msg_doc, msg);
  if (topic == subscribe_topics[0])
  {
    bool motion = msg_doc["motion"];
    if (motion == true)
      digitalWrite(leds[0], HIGH);s
    else
      digitalWrite(leds[0], LOW);
  }
  else if (topic == subscribe_topics[1])
  {
    if (current_millis - prev_millis >= led2_interval)
    {
      prev_millis = current_millis;
      if (led2_state == LOW)
        led2_state = HIGH;
      else
        led2_state = LOW;
      digitalWrite(leds[1], led2_state);
    }
    float distance = msg_doc["distance"];
    if (distance <= 5.0)
      led2_interval = 500;
    else if (distance < 5.0 && distance < 10)
      led2_interval = 2000;
    else {
      led2_interval = 1000000;
      digitalWrite(leds[1], LOW);
    }
  }
  else if (topic == subscribe_topics[2])
  {
    float temperature = msg_doc["temperature"];
    if (temperature != prev_temp)
    {
      digitalWrite(leds[2], HIGH);
      prev_temp = temperature;
    }
    else
      digitalWrite(leds[2], LOW);
  }
  else
  { // ignore
  }
  mqtt_client.reset_msg();
}
