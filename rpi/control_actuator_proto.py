import mqtt_client
import amqp_client
import http_client
import json


def on_amqp_message(channel, method, properties, msg):
    print("actuator-controller - AMQP consumer - Message received: " + msg.decode("utf-8"))
    payload_rabbit = str(msg.decode("utf-8"))
    print("actuator-controller - HTTP GET - Retrieving message from Elasticsearch...")
    res_elastic = http_client.query(url_elastic + "/" + index_elastic + "/_search",method="GET")
    payload_elastic = None
    if res_elastic is not None:
        if res_elastic["hits"]["total"]["value"] > 0:
            hits = res_elastic["hits"]["hits"]
            last_hit = hits[len(hits) - 1]
            payload_elastic = json.dumps(last_hit["_source"])
    if payload_elastic is not None:
        print("actuator-controller - MQTT publisher - Forwarding data from Elasticsearch to Mosquitto: " + payload_elastic)
        mqttc.publish(actuator1_topic_mosquitto, payload_elastic)
    if payload_rabbit is not None:
        print("actuator-controller - MQTT publisher - Forwarding data from Rabbitmq to Mosquitto: " + payload_rabbit)
        mqttc.publish(actuator2_topic_mosquitto, payload_rabbit)


url_elastic = "http://SERVER_IP:9200"
index_elastic = "notelab"
ip_rabbit = "MQTT_BROKER_IP"
port_rabbit = 5672
user_rabbit = "user"
pass_rabbit = "password"
exchange_rabbit = "amq.topic"
r_key_rabbit = "notelab"
queue_rabbit = "notelab_queue"
ip_mosquitto = "RaspberryPi_IP"
actuator1_topic_mosquitto = "test_topic_1"
actuator2_topic_mosquitto = "test_topic_2"

mqttc = mqtt_client.connect(ip_mosquitto) 

amqp_client.message = None
amqp_channel = amqp_client.connect_to_broker(ip_rabbit, port=port_rabbit, user=user_rabbit, passw=pass_rabbit) 
amqp_client.subscribe(amqp_channel, queue_rabbit, on_amqp_message)
try:
    amqp_channel.start_consuming()
except KeyboardInterrupt:
    amqp_channel.stop_consuming()
amqp_channel.close()
