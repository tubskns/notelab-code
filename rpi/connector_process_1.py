import mqtt_client
import amqp_client
import json, time
import logging

# rabbit
ip_rabbit = "192.168.1.7"
exchange_rabbit = "amq.topic"
rkey_rabbit_temp = "notelab"
queue_rabbit_temp = "notelab"
rkey_rabbit_dist = "dist_rabbit"
queue_rabbit_dist = "dist_rabbit"
rkey_rabbit_motion = "motion_rabbit"
queue_rabbit_motion = "motion_rabbit"

# mosquitto
ip_mosquitto = "192.168.1.3"
topic_temp = "temp_topic"
topic_dist = "dist_topic"
topic_motion = "motion_topic"
topics_mosquitto = [
    (topic_temp, 1),
    (topic_dist, 1),
    (topic_motion, 1),
]

# global vars
is_activated = False
activation_interval = 5
start_time = 100000000
temp_values = []
logging.basicConfig(
    format="%(asctime)s | %(name)s | %(levelname)s | %(message)s", level=logging.INFO
)

logging.info("Running connector... ")

# connect to rabbitmq
amqp_channel = amqp_client.connect_to_broker(
    ip_rabbit, port=5672, user="user", passw="password"
)
amqp_client.create_queue(
    amqp_channel, exchange_rabbit, rkey_rabbit_temp, queue_rabbit_temp
)
amqp_client.create_queue(
    amqp_channel, exchange_rabbit, rkey_rabbit_dist, queue_rabbit_dist
)
amqp_client.create_queue(
    amqp_channel, exchange_rabbit, rkey_rabbit_motion, queue_rabbit_motion
)

# connect to mosquitto and subscribe to topics
mqtt_client.message = None
mqttc = mqtt_client.connect(ip_mosquitto)
mqttc.subscribe(topics_mosquitto)
mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        topic = mqtt_client.message.topic
        msg = json.loads(str(mqtt_client.message.payload.decode("utf-8")))
        if topic == topic_motion:  # check to activate workflow based on motion
            if msg["motion"]:
                if not is_activated:  # activate circuit
                    is_activated = True
                    start_time = time.time()
                    amqp_channel.basic_publish(
                        exchange=exchange_rabbit,
                        routing_key=rkey_rabbit_motion,
                        body=json.dumps(msg),
                    )
                else:
                    elapsed_time = time.time() - start_time
                    if elapsed_time > activation_interval:  # deactivate circuit
                        amqp_channel.basic_publish(
                            exchange=exchange_rabbit,
                            routing_key=rkey_rabbit_motion,
                            body=json.dumps(msg),
                        )
                        is_activated = False
        elif topic == topic_temp:  # calculate avg temp of x values and send
            if len(temp_values) < 24:
                temp_values.append(msg["temperature"])
            else:
                avg_temp = sum(temp_values) / len(temp_values)
                msg["temperature"] = avg_temp
                amqp_channel.basic_publish(
                    exchange=exchange_rabbit,
                    routing_key=rkey_rabbit_temp,
                    body=json.dumps(msg),
                )
                temp_values = []
        elif topic == topic_dist:
            if is_activated:
                amqp_channel.basic_publish(
                    exchange=exchange_rabbit,
                    routing_key=rkey_rabbit_dist,
                    body=json.dumps(msg),
                )
        mqtt_client.message = None  # reset message
