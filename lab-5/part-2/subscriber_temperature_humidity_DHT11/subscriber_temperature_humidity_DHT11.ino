#include "mqtt_client.h"
#include "connect_WLAN.h"
#include <ArduinoJson.h>

#define LED D1 //external LED is connected to NodeMCU's pin GPIO5 (D1)
// #define LED 13 //external LED is connected to WeMos's pin GPIO14

String ssid_wifi = "netw1";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
char* mqtt_topic = "topic_test";
char* message = "message_test";

float temperature = 0;
float humidity = 0;
float blink_delay = 100;

void setup()
{
  Serial.begin(9200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  connect_to_broker();
  Serial.print("Subscribing to topic: ");
  Serial.println(mqtt_topic);
  subscribe_to_topic(mqtt_topic);
  pinMode(LED, OUTPUT); // initialize LED as an output
}

void loop()
{
  check_connection();
  String buffer = get_buffer();
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message);

  temperature = doc["temperature"];
  // humidity = doc["humidity"];

  // Generate the prettified JSON and send it to the Serial port.
  serializeJsonPretty(doc, Serial);

  if (temperature >= 10.0)
  {
    blink_delay = 2000;
  }
  else if (temperature >= 20.0)
  {
    blink_delay = 500;
  } else 
  {
    blink_delay = 100;
  }
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);                       // wait
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(blink_delay);                       // wait 
}
