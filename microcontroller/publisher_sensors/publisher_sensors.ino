#include "mqtt_client.h"
#include "wifi_connection.h"
#include "interface_DHT11.h"
#include "interface_HCSR04.h"
#include "interface_PIR.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
const char* client_id = "publisher_sensors";
char* mqtt_topic1 = "temperature_topic";
char* mqtt_topic2 = "distance_topic";
char* mqtt_topic3 = "motion_topic";

void setup(){
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  //initialize_sensor();
}

void loop(){
  check_connection(client_id);
  //temperature sensor
  float temperature = get_temperature();
  String temperature_str = String(temperature); // convert float to string
  Serial.print("Temperature: " + temperature_str + " *C\n");
  //distance sensor
  int distance = calculate_distance();
  String distance_str = String(distance); // convert int to string
  Serial.print("Distance: " + distance_str + " cm\n");
  //motion sensor
   bool is_motion = detect_motion();
  if (is_motion == true)
  {
    Serial.println("Motion detected!");
  }
  else
  {
    Serial.println("Motion absent!");
  }
  delay(1000);
  
  DynamicJsonDocument doc1(1024), doc2(1024), doc3(1024);
  doc1["id"] = "publisher_sensor";
  doc1["temperature"] = temperature;
  doc2["id"] = "publisher_sensor";
  doc2["distance"] = distance;
  doc3["id"] = "publisher_sensor";
  doc3["motion"] = is_motion;
  // Generate the prettified JSON and send it to the Serial port
  // serializeJsonPretty(doc, Serial);

  String json_doc1, json_doc2, json_doc3;
  serializeJson(doc1, json_doc1);
  char buf1[500], buf2[500], buf3[500] ;
  json_doc1.toCharArray(buf1, 500);
  json_doc2.toCharArray(buf2, 500);
  json_doc3.toCharArray(buf3, 500);
  publish_message(mqtt_topic1, buf1);
  publish_message(mqtt_topic2, buf2);
  publish_message(mqtt_topic3, buf3);
  delay(5000);
}
