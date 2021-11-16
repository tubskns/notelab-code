#include "mqtt_client.h"
#include "connect_WLAN.h"

String ssid_wifi = "netw1";     // student's network SSID
String pass_wifi = "password1"; //student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883;          // MQTT port (default :1883)
char* mqtt_topic = "topic_test";
char* message = "message_test";

void setup()
{
    Serial.begin(115200); // establish serial communication at baud rate 115200
    connect_to_wifi(ssid_wifi, pass_wifi);
    initialize_client(mqtt_broker_ip, mqtt_broker_port);
    subscribe_to_topic(mqtt_topic);
    publish_message(mqtt_topic, message);
}

void loop()
{
    check_connection();
}