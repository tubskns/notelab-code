#include <Arduino.h>
#include <MQTT.h>

class MqttClient
{
  public:
    MqttClient(const char* mqtt_broker_ip, const int mqtt_broker_port);
    MqttClient(const char* mqtt_broker_ip, const int mqtt_broker_port, String *subscribe_topics, const int num_subscribe_topics);
    void connect(const char* client_id);
    void publish_message(const char *topic, const char *msg);
    void check_connection(const char* client_id);
    String get_msg();
    String get_topic();
    void reset_msg();
  private:
    MQTTClient _mqtt_client{_newBufferSize};
    String *_subscribe_topics;
    int _num_subscribe_topics;
    static constexpr int _newBufferSize = 1024;
};