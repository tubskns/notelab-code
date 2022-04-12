#include <Arduino.h>

void connect(const char* client_id, String *topics, int num_topics);

void initialize_client(const char* mqtt_broker_ip, const int mqtt_broker_port);

void subscribe_to_topic(char* topic);

void publish_message(char* topic, char* msg);

void check_connection(const char* client_id, String *topics, int num_topics);

String get_msg();

String get_topic();

void reset_msg();
