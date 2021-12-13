import mqtt_client
import amqp_pub


def process_temp(data):
    return data


def process_dist(data):
    return data


def process_motion(data):
    return data


# parameters
ip_rabbitmq = "127.0.0.1"
ip_broker_mqtt = "127.0.0.1"
temp_topic = "temperature_topic"
dist_topic = "distance_topic"
motion_topic = "motion_topic"
topics_mqtt = [
    (temp_topic, 1),
    (dist_topic, 1),
    (motion_topic, 1),
]

# connect to rabbitmq
amqp_channel = amqp_pub.connect_to_rabbitmq(ip_rabbitmq)

# connect to mqtt broker and subscribe to topics
mqtt_client.message = None
mqttc = mqtt_client.connect(ip_broker_mqtt)
mqttc.subscribe(topics_mqtt)

# start mqtt loop
mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        # retrieve topic and payload
        topic = mqtt_client.message
        payload = str(mqtt_client.message.payload.decode("utf-8"))
        # process payload based on topic
        if topic is temp_topic:
            payload = process_temp(payload)
        elif topic is dist_topic:
            payload = process_dist(payload)
        elif topic is motion_topic:
            payload = process_motion(payload)
        # forward payload to amqp server
        if payload is not None:
            amqp_pub.send_message_to_rabbitmq(
                amqp_channel,
                payload,
            )
        # reset message
        mqtt_client.message = None
