import mqtt_client
import rpi.amqp_client as amqp_client
import json


def process_temp(msg, previous_msg):
    print("Processing temperature...")
    temp = msg["temperature"]
    if previous_msg is not None:
        previous_temp = previous_msg["temperature"]
        if temp != previous_temp:
            print("temperature updated")
        else:
            msg = None
            print("no temperature update")
    return msg


def process_dist(msg):
    print("Processing distance...")
    distance = msg["distance"]
    if distance < 5:
        msg["priority"] = "high"
        print("added high priority")
    elif 5 <= distance <= 10:
        msg["priority"] = "medium"
        print("added medium priority")
    elif distance > 10:
        msg = None
        print("no priority added")
    return msg


def process_motion(msg, previous_msg):
    print("Processing motion detection...")
    motion = msg["motion"]
    if previous_msg is not None:
        previous_motion = previous_msg["motion"]
        if motion != previous_motion:
            print("motion status updated")
        else:
            msg = None
            print("no motion status updated")
    return msg


# parameters
ip_rabbitmq = "localhost"
ip_broker_mqtt = "broker.hivemq.com"
temp_topic = "temperature_topic"
dist_topic = "distance_topic"
motion_topic = "motion_topic"
topics_mqtt = [
    (temp_topic, 1),
    (dist_topic, 1),
    (motion_topic, 1),
]

# connect to rabbitmq
amqp_channel = amqp_client.connect_to_rabbitmq(ip_rabbitmq)

# connect to mqtt broker and subscribe to topics
mqtt_client.message = None
mqttc = mqtt_client.connect(ip_broker_mqtt)
mqttc.subscribe(topics_mqtt)
last_payload = None

# start mqtt loop
mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        # retrieve topic and payload
        topic = mqtt_client.message.topic
        payload = json.loads(str(mqtt_client.message.payload.decode("utf-8")))
        # process payload based on topic
        if topic == temp_topic:
            payload = process_temp(payload, last_payload)
        elif topic == dist_topic:
            payload = process_dist(payload)
        elif topic == motion_topic:
            payload = process_motion(payload, last_payload)
        # forward payload to amqp server
        if payload is not None:
            payload_str = json.dumps(payload)
            amqp_client.send_message_to_rabbitmq(
                amqp_channel,
                payload_str,
            )
            last_payload = payload
        # reset message
        mqtt_client.message = None
