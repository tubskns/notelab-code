#include "MqttClient.h"
#include "WifiClient.h"

String ssid_wifi = "netw1";
String pass_wifi = "password1";

const char *mqtt_broker_ip = "broker.hivemq.com";
const int mqtt_broker_port = 1883;
const char *client_id = "client_id";
const int num_subscribe_topics = 1;
String subscribe_topics[num_subscribe_topics] = {"topic_test"};
const char *publish_topic = "topic_test";
const char *publish_message = "message_test";
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port, subscribe_topics, num_subscribe_topics);

void setup()
{
    Serial.begin(9200);
    wifi_client.connect();
    mqtt_client.connect(client_id);
    mqtt_client.publish_message(publish_topic, publish_message);
}

void loop()
{
    mqtt_client.check_connection(client_id);
}
