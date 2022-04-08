#include "mqtt_client.h"
#include "wifi_connection.h"
#include "PIR.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
const char* client_id = "publisher_PIR";
char* mqtt_topic = "motion_topic";

const int pirSensor = 13; // PIR's pin is connected to NodeMCU's GPIO13 (D7) or WeMos GPIO13 (D7)
PIR pir(pirSensor);

void setup()
{
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
}


void loop()
{
  check_connection(client_id);
  bool is_motion = pir.detect_motion();
  if (is_motion == true)
  {
    Serial.println("Motion detected!");
  }
  else
  {
    Serial.println("Motion absent!");
  }
  delay(1000);
  
  DynamicJsonDocument doc(1024);

  doc["id"] = "publisher_PIR";
  doc["motion"] = is_motion;
  // Generate the prettified JSON and send it to the Serial port
  // serializeJsonPretty(doc, Serial);

  String json_doc;
  serializeJson(doc, json_doc);

  char buf[500];
  json_doc.toCharArray(buf, 500);
  publish_message(mqtt_topic, buf);

  delay(5000);
}
