#include <Arduino.h>

class MqttClient
{
  public:
    MqttClient(WiFiClient wifi_client, const char* mqtt_broker_ip, const int mqtt_broker_port);
    void connect(const char* client_id, String *topics, int num_topics);
    void publish_message(char *topic, char *msg);
    void check_connection(const char* client_id, String *topics, int num_topics);
    String get_msg();
    String get_topic();
    void reset_msg();
  private:
    MQTTClient _mqtt_client;
    String _msg;
    String _topic;
};