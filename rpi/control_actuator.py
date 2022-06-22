import mqtt_client, amqp_client, http_client
import json
import logging

def on_motion_message(channel, method, properties, msg):
    global IS_ACTIVATED
    msg = json.loads(str(msg.decode("utf-8")))
    if msg is not None:
        if msg["motion"]:
            if not IS_ACTIVATED:
                mqttc.publish(motion_led_topic, json.dumps(msg))
                IS_ACTIVATED = True
        else:
            mqttc.publish(motion_led_topic, json.dumps(msg))
            IS_ACTIVATED = False


def on_dist_message(channel, method, properties, msg):
    msg = str(msg.decode("utf-8"))
    if msg is not None:
        if IS_ACTIVATED:
            mqttc.publish(dist_led_topic, msg)
            res_elastic = http_client.query(
                url_elastic + "/" + index_elastic + "/_search", method="GET"
            )
            if res_elastic is not None:
                if res_elastic["hits"]["total"]["value"] > 0:
                    hits = res_elastic["hits"]["hits"]
                    for i in range(len(hits)):
                        current_hit = hits[i]
                        hit_source = json.dumps(current_hit["_source"])
                        if hit_source is not None:
                            mqttc.publish(temp_led_topic, hit_source)


# elasticsearch
url_elastic = "http://192.168.1.7:9200"
index_elastic = "notelab"

# rabbitmq
ip_rabbit = "192.168.1.7"
exchange_rabbit = "amq.topic"
dist_r_key_rabbit = "dist_rabbit"
dist_queue_rabbit = "dist_rabbit"
motion_r_key_rabbit = "motion_rabbit"
motion_queue_rabbit = "motion_rabbit"

# mosquitto
ip_mosquitto = "192.168.1.3"
motion_led_topic = "motion_led_topic"
temp_led_topic = "temp_led_topic"
dist_led_topic = "dist_led_topic"

# global vars
IS_ACTIVATED = False
logging.basicConfig(
    format="%(asctime)s | %(name)s | %(levelname)s | %(message)s", level=logging.INFO
)

logging.info("Running connector... ")
mqttc = mqtt_client.connect(ip_mosquitto)

amqp_client.message = None
amqp_channel = amqp_client.connect_to_broker(
    ip_rabbit, port=5672, user="user", passw="password"
)
amqp_client.subscribe(amqp_channel, dist_queue_rabbit, on_dist_message)
amqp_client.subscribe(amqp_channel, motion_queue_rabbit, on_motion_message)
try:
    amqp_channel.start_consuming()
except KeyboardInterrupt:
    amqp_channel.stop_consuming()
amqp_channel.close()
