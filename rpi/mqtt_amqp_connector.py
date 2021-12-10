import mqtt_sub
import amqp_pub
import sensor_data as sd

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
DEFAULT_TOPIC = "default_topic"
TEMP_TOPIC = "temperature_topic"
DIST_TOPIC = "distance_topic"
MOTION_TOPIC = "motion_topic"
TOPICS_MQTT = [
    (DEFAULT_TOPIC, 1),
    (TEMP_TOPIC, 1),
    (DIST_TOPIC, 1),
    (MOTION_TOPIC, 1),
]

# redefines on_message callback function
# client receives message from mqtt broker and resends to rabbitmq
def on_message(client, userdata, msg):
    msg_str = str(msg.payload.decode("utf-8"))
    print("MQTT Broker - message received [" + msg.topic + "]: " + msg_str)
    processed_data = ""
    if msg.topic is TEMP_TOPIC:
        processed_data = sd.process_temp(msg_str)
    elif msg.topic is DIST_TOPIC:
        processed_data = sd.process_dist(msg_str)
    elif msg.topic is MOTION_TOPIC:
        processed_data = sd.process_motion(msg_str)
    else:
        processed_data = sd.process_default(msg_str)
    amqp_pub.send_message_to_rabbitmq(
        channel, EXCHANGE_RABBITMQ, ROUTING_KEY_RABBITMQ, processed_data
    )
    print("RabbitMQ - Message sent to server: " + msg_str)


# connect to mqtt broker
mqttc = mqtt_sub.connect_to_mqtt_broker(IP_BROKER_MQTT, PORT_BROKER_MQTT)
mqttc.on_message = on_message

# subscribe to mqtt topic
mqttc.subscribe(TOPICS_MQTT)
mqttc.loop_forever()
