import mqtt_client, amqp_client, http_client
import time
import json

# elastic
url_elastic = "http://192.168.1.7:9200"
index_elastic = "notelab"
# rabbit
ip_rabbit = "134.169.115.45"
exchange_rabbit = "amq.topic"
r_key_rabbit = "notelab"
queue_rabbit = "notelab_queue"
# mosquitto
ip_mosquitto = "192.168.1.3"
actuator1_topic_mosquitto = "test_topic_1"
actuator2_topic_mosquitto = "test_topic_2"

# connect to mosquitto
mqttc = mqtt_client.connect(ip_mosquitto)


def on_amqp_message(channel, method, properties, msg):
    # rabbit
    print("Connector_2 - AMQP consumer - Message received: " + msg.decode("utf-8"))
    payload_rabbit = str(msg.decode("utf-8"))
    # elastic
    print("Connector_2 - HTTP GET - Retrieving message from Elasticsearch...")
    res_elastic = http_client.query(
        url_elastic + "/" + index_elastic + "/_search",
        method="GET",
    )
    payload_elastic = None
    if res_elastic is not None:
        if res_elastic["hits"]["total"]["value"] > 0: 
            hits = res_elastic["hits"]["hits"]
            last_hit = hits[len(hits) - 1]
            msg = last_hit["_source"]
            payload_elastic = json.dumps(msg)
    # mosquitto
    if payload_elastic is not None:
        print("Connector_2 - MQTT publisher - Forwarding data from Elasticsearch to Mosquitto: " + payload_elastic)
        mqttc.publish(actuator1_topic_mosquitto, payload_elastic)
    if payload_rabbit is not None:
        print("Connector_2 - MQTT publisher - Forwarding data from Rabbitmq to Mosquitto: " + payload_rabbit)
        mqttc.publish(actuator2_topic_mosquitto, payload_rabbit)


# connect to rabbitmq and subscribe to topics
amqp_client.message = None
amqp_channel = amqp_client.connect_to_broker(
    ip_rabbit, port=5672, user="user", passw="password"
)
amqp_client.subscribe(amqp_channel, queue_rabbit, on_amqp_message)
