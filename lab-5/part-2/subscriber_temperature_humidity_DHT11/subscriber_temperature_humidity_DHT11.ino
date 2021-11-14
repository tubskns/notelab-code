#include "mqtt_client.h"
#include "connect_WLAN.h"
#include "temperature_humidity_DHT11.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw1";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char *mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
char *mqtt_topic = "topic_test";
char *message = "message_test";

// client receives message from broker
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  String message;
  for (int i = 0; i < length; i++)
  {
    message = message + (char)payload[i];
  }
  Serial.println(message);
  // add a condition for turning on a LED
  if (message[39] == '2' && message[40] == '5')
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  connect_to_broker();
  Serial.print("Subscribing to topic: ");
  Serial.println(mqtt_topic);
  subscribe_to_topic(mqtt_topic);
  initialize_sensor();
  pinMode(LED, OUTPUT); // initialize LED as an output
}

void loop()
{
  check_connection();
  mqttClient.loop();
}
