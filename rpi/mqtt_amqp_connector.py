import mqtt_sub
import amqp_pub

#########################
####### rabbitmq ########
#########################

# parameters
IP_RABBITMQ = "192.168.1.7"
PORT_RABBITMQ = 5672
USER_RABBITMQ = "user"
PASS_RABBITMQ = "password"
QUEUE_RABBITMQ = "notelab"
EXCHANGE_RABBITMQ = "amq.topic"
ROUTING_KEY_RABBITMQ = "logstash"

# connect to rabbitmq
channel = amqp_pub.connect_to_rabbitmq(
    IP_RABBITMQ, PORT_RABBITMQ, USER_RABBITMQ, PASS_RABBITMQ, QUEUE_RABBITMQ
)


#####################
####### mqtt ########
#####################

# parameters
IP_BROKER_MQTT = "192.168.1.3"
PORT_BROKER_MQTT = 1883
TOPIC_MQTT = "notelab/test_MQTT-AMQP_connector"

# redefines on_message callback function
# client receives message from mqtt broker and resends to rabbitmq
def on_message(client, userdata, msg):
    msg_str = str(msg.payload.decode("utf-8"))
    print("MQTT Broker - message received [" + msg.topic + "]: " + msg_str)
    amqp_pub.send_message_to_rabbitmq(
        channel, EXCHANGE_RABBITMQ, ROUTING_KEY_RABBITMQ, msg_str
    )
    print("RabbitMQ - Message sent to server: " + msg_str)


# connect to mqtt broker
mqttc = mqtt_sub.connect_to_mqtt_broker(IP_BROKER_MQTT, PORT_BROKER_MQTT)
mqttc.on_message = on_message

# subscribe to mqtt topic
mqttc.subscribe(TOPIC_MQTT)
mqttc.loop_forever()
