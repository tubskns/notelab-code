import mqtt_client
import amqp_client
import json, time
import logging


ip_rabbit = "SERVER_IP"
port_rabbit = 30672
user_rabbit = "user"
pass_rabbit = "password"
ex_rabbit = "amq.topic"
rkey_rabbit_temp = "temperature"
queue_rabbit_temp = "temperature"
rkey_rabbit_dist = "dist_rabbit"
queue_rabbit_dist = "dist_rabbit"
rkey_rabbit_motion = "motion_rabbit"
queue_rabbit_motion = "motion_rabbit"

ip_mosquitto = "MQTT_BROKER_IP"
topic_temp = "temp_topic"
topic_dist = "dist_topic"
topic_motion = "motion_topic"
topics_mosquitto = [
    (topic_temp, 1),
    (topic_dist, 1),
    (topic_motion, 1),
]

IS_ACTIVATED = False
activation_interval = 5
start_time = 100000000
temp_values = []
logging.basicConfig(format="%(asctime)s | %(name)s | %(levelname)s | %(message)s", level=logging.INFO)

amqp_ch = amqp_client.connect_to_broker(ip_rabbit, port=port_rabbit, user=user_rabbit, passw=pass_rabbit)
amqp_client.create_queue(amqp_ch, ex_rabbit, rkey_rabbit_temp, queue_rabbit_temp)
amqp_client.create_queue(amqp_ch, ex_rabbit, rkey_rabbit_dist, queue_rabbit_dist)
amqp_client.create_queue(amqp_ch, ex_rabbit, rkey_rabbit_motion, queue_rabbit_motion)

mqtt_client.message = None
mqttc = mqtt_client.connect(ip_mosquitto)
mqttc.subscribe(topics_mosquitto)
mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        topic = mqtt_client.message.topic
        msg = json.loads(str(mqtt_client.message.payload.decode("utf-8")))
        if IS_ACTIVATED:
            elapsed_time = time.time() - start_time
            if elapsed_time > activation_interval:
                logging.debug("Activation interval is over")
                IS_ACTIVATED = False
                logging.debug("STOPPING collection of distance...")
                msg_motion = {}
                msg_motion["motion"] = False
                amqp_ch.basic_publish(ex_rabbit, rkey_rabbit_motion, json.dumps(msg_motion))
                logging.debug("RESETTING distance to 0... ")
                msg_dist = {}
                msg_dist["distance"] = 0.0
                amqp_ch.basic_publish(ex_rabbit, rkey_rabbit_dist, json.dumps(msg_dist))
        if topic == topic_motion:
            if msg["motion"] and IS_ACTIVATED == False:
                logging.debug("STARTING collection of distance...")
                IS_ACTIVATED = True
                start_time = time.time()
                amqp_ch.basic_publish(ex_rabbit, rkey_rabbit_motion, json.dumps(msg))
        elif topic == topic_temp:
            if len(temp_values) < 24:
                temp_values.append(msg["temperature"])
            else:
                logging.debug("Sending average temperature... ")
                avg_temp = sum(temp_values) / len(temp_values)
                msg["temperature"] = avg_temp
                amqp_ch.basic_publish(ex_rabbit, rkey_rabbit_temp, json.dumps(msg))
                temp_values = []
        elif topic == topic_dist:
            if IS_ACTIVATED:
                logging.debug("SENDING distance... ")
                amqp_ch.basic_publish(ex_rabbit, rkey_rabbit_dist, json.dumps(msg))
        mqtt_client.message = None
