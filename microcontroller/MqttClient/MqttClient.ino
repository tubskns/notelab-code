#include "MqttClient.h"
#include "WiFiConnect.h"

String ssid_wifi = "netw1";     
String pass_wifi = "password1"; 

const char *mqtt_broker_ip = "192.168.1.3"; 
const int mqtt_broker_port = 1883;  
const char *client_id = "client_id";

MqttClient mqtt_client;

void setup()
{
    Serial.begin(115200);
    WiFiConnect wifi_connect(ssid_wifi, pass_wifi);
    mqtt_client(wifi_connect, mqtt_broker_ip, mqtt_broker_port)

        String subscribe_topics[1] = {"topic_test"};
    mqtt_client.connect(client_id, subscribe_topics, (sizeof(subscribe_topics) / sizeof(subscribe_topics[0])));

    char *publish_topic = "topic_test";
    char *publish_msg = "message_test";
    mqtt_client.publish_message(publish_topic, publish_msg);
}

void loop()
{
    check_connection(client_id);
}
