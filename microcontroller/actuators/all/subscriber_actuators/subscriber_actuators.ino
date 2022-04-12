#include "mqtt_client.h"
#include "wifi_connection.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";
String pass_wifi = "password1";
const char *mqtt_broker_ip = "192.168.1.3";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_sensors";
char *temp_topic = "temperature_topic";
char *dist_topic = "distance_topic";
char *motion_topic = "motion_topic";
#define LED1 D1 // green LED connected to GPIO5 (D1)
#define LED2 D2 // yellow LED is connected to GPIO4 (D2)
#define LED3 D3 // red LED is connected to GPIO (D3)
DynamicJsonDocument msg_doc(1024);
float prev_temp = 0;

void setup()
{
  Serial.begin(115200);
  connect_to_wifi(ssid_wifi, pass_wifi);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  connect(client_id);
  subscribe_to_topic(temp_topic);
  subscribe_to_topic(dist_topic);
  subscribe_to_topic(motion_topic);
}

void loop(){
  check_connection(client_id);
  String msg = get_msg();
  String topic = get_topic();
  deserializeJson(msg_doc, msg);
  if (topic == motion_topic){
    bool motion = msg_doc["motion"];
    if (motion == true){
      digitalWrite(LED1, HIGH);
    }
    else{
      digitalWrite(LED1, LOW);
    }
  }
  else if (topic == dist_topic){
    float distance = msg_doc["distance"];
    float blink_delay=0;
    if (distance >= 1.0 && distance < 5.0){
      blink_delay = 500;
    }
    else if (distance >= 5.0 && distance < 10.0){
      blink_delay = 1000;
    }
    else{
      blink_delay = 2000;
    }
    digitalWrite(LED2, HIGH);
    delay(blink_delay);
    digitalWrite(LED2, LOW);
    delay(blink_delay);
  }
  else if (topic == temp_topic){
    float temperature = msg_doc["temperature"];
    if (temperature != prev_temp){
      digitalWrite(LED3, HIGH);
      prev_temp = temperature;
    } else {
      digitalWrite(LED3, LOW);
    }
  }
  else{Serial.println("Topic not matching, ignoring...");}
}
