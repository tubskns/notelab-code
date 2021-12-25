import mqtt_client
import amqp_pub
import json

lastValue = 0

def process_temp(data):
    print("Processing temperature...")
    return data


def process_dist(data):
    print("Processing distance...")
    distance = data["distance"]
    if distance < 5:
        data["priority"] = "high"
        print("added high priority")
    elif 5 <= distance <= 10:
        data["priority"] = "medium"
        print("added medium priority")
    elif distance > 10:
        data = None
        print("no priority added")
    return data


def process_motion(data):
    print("Processing motion detection...")
    return data


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
        topic = mqtt_client.message.topic
        payload = json.loads(str(mqtt_client.message.payload.decode("utf-8")))
        # process payload based on topic
        if topic == temp_topic:
            payload = process_temp(payload)
        elif topic == dist_topic:
            payload = process_dist(payload)
        elif topic == motion_topic:
            payload = process_motion(payload)
        # forward payload to amqp server
        if payload is not None:
            payload = json.dumps(payload)
            amqp_pub.send_message_to_rabbitmq(
                amqp_channel,
                payload,
            )
        # reset message
        mqtt_client.message = None
