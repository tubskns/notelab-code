#include "mqtt_client.h"
#include "wifi_connection.h"
#include <ArduinoJson.h>

String ssid_wifi = "netw0";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
const char* client_id = "subscriber_all_sensors";
char* mqtt_topic1 = "temperature_topic";
char* mqtt_topic2 = "distance_topic";
char* mqtt_topic3 = "motion_topic";

//Pin variables 
#define LED1 D1 //green external LED connected to NodeMCU's pin GPIO5 (D1)
#define LED2 D2 //yellow external LED is connected to NodeMCU's pin GPIO4 (D2)
#define LED3 D3 //red external LED is connected to NodeMCU's pin GPIO (D3)

float temperature = 0;
float prev_temp = 0; // store the previous value of temperature
float humidity = 0;
float distance = 0;
bool motion = true;
float blink_delay = 100;

void setup(){
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port); 
  connect(client_id);
  subscribe_to_topic(mqtt_topic1);  
  subscribe_to_topic(mqtt_topic2);  
  subscribe_to_topic(mqtt_topic3);
  pinMode(LED1, OUTPUT); // initialize green LED as an output
  pinMode(LED2, OUTPUT); // initialize yellow LED as an output
  pinMode(LED3, OUTPUT); // initialize red LED as an output
}

void loop(){
  check_connection(client_id);
  String buffer1 = get_buffer();
  String buffer2 = get_buffer();
  String buffer3 = get_buffer();
  DynamicJsonDocument doc1(1024), doc2(1024), doc3(1024);
  deserializeJson(doc1, buffer1);
  deserializeJson(doc2, buffer2);
  deserializeJson(doc3, buffer3);
  temperature = doc1["temperature"];
  delay(100);
  prev_temp = temperature;
  delay(100);
  temperature = doc1["temperature"];
  Serial.println(temperature);
  distance = doc2["distance"];
  Serial.println(distance); 
  motion = doc3["motion"];
  Serial.println(motion); 

  //motion sensor actuation
  if (motion = true){
  digitalWrite(LED1, HIGH); // turn the LED on (HIGH is the voltage level)
  }
   //distance sensor actuation
  if (distance >= 1.0 && distance < 5.0){
  blink_delay = 500;
  }
  else if (distance >= 5.0 && distance < 10.0 ){
  blink_delay = 1000;
  }
  else{
    blink_delay = 2000;
  }
  digitalWrite(LED2, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);      // wait
  digitalWrite(LED2, LOW);  // turn the LED off by making the voltage LOW
  delay(blink_delay);      // wait

    //temperature sensor actuation
  if (temperature != prev_temp){
    digitalWrite(LED3, HIGH);
    prev_temp = temperature;
    digitalWrite(LED3, LOW);
  }
  
}
