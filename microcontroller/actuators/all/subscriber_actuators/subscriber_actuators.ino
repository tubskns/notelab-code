#include "mqtt_client.h"
#include "wifi_connection.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";
String pass_wifi = "password1";
const char *mqtt_broker_ip = "192.168.1.3";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_sensors";
String topics[3] = {"motion_topic", "dist_topic", "temp_topic"};
uint8_t leds[3] = {D1, D2, D3}; // green, yellow, red
DynamicJsonDocument msg_doc(1024);
float prev_temp = 0;
int led2_state = LOW;
long led2_interval = 1000000;
unsigned long prev_millis = 0;

void setup()
{
  Serial.begin(115200);
  connect_to_wifi(ssid_wifi, pass_wifi);
  for (int i = 0; i < (sizeof(leds) / sizeof(leds[0])); i++)
    pinMode(leds[i], OUTPUT);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
}

void loop()
{
  check_connection(client_id, topics, (sizeof(topics) / sizeof(topics[0])));
  String msg = get_msg();
  String topic = get_topic();
  unsigned long current_millis = millis();
  deserializeJson(msg_doc, msg);
  if (topic == topics[0])
  {
    bool motion = msg_doc["motion"];
    if (motion == true)
      digitalWrite(leds[0], HIGH);
    else
      digitalWrite(leds[0], LOW);
  }
  else if (topic == topics[1])
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
  else if (topic == topics[2])
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
  reset_msg();
}
