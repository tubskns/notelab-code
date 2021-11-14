#include "mqtt_client.h"
#include <PubSubClient.h> // MQTT client library
#include <ESP8266WiFi.h>

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void connect_to_broker()
{
    // check when request is accepted by the broker
    while (!mqtt_client.connected())
    {
        Serial.print("Connecting to MQTT broker...");
        if (mqtt_client.connect("ESP8266 Client"))
        {
            Serial.println(" connection established!");
        }
        else
        {
            Serial.print("Connection failed! [rc=");
            Serial.print(mqtt_client.state());
            Serial.println("], retrying....");
            delay(5000); // wait before retrying
        }
    }
}

// client receives message from broker
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");
    for(int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void initialize_client(const char* mqtt_broker_ip, const int mqtt_broker_port)
{
    mqtt_client.setServer(mqtt_broker_ip, mqtt_broker_port); // instance of MQTT client, specify the address and the port of the MQTT broker
}

void subscribe_to_topic(char* topic){
    mqtt_client.setCallback(callback); //handle incoming MQTT messages
    mqtt_client.subscribe(topic); // subscribe to the topic
}

void publish_message(char* topic, char* msg)
{
    mqtt_client.publish(topic, msg); // publish to the topic
}

void check_connection()
{
    if (!mqtt_client.connected()) {
        connect_to_broker();
    }
    mqtt_client.loop();
}

