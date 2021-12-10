#include "mqtt_client.h"
#include "wifi_connection.h"
#include "interface_DHT11.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw1";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
const char* client_id = "publisher_DHT11";
char* mqtt_topic = "notelab/temperature&humidity";

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  initialize_sensor();
}

void loop()
{
  check_connection(client_id);
  float humidity = get_humidity();
  String humidity_str = String(humidity); // convert float to string
  Serial.print("Humidity: " + humidity_str + " %\n");
  float temperature = get_temperature();
  String temperature_str = String(temperature); // convert float to string
  Serial.print("Temperature: " + temperature_str + " *C\n");

  DynamicJsonDocument doc(1024);

  doc["id"] = "publisher_DHT11";
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  // Generate the prettified JSON and send it to the Serial port
  // serializeJsonPretty(doc, Serial);

  String json_doc;
  serializeJson(doc, json_doc);

  char buf[500];
  json_doc.toCharArray(buf, 500);
  publish_message(mqtt_topic, buf);

  delay(5000);
}
