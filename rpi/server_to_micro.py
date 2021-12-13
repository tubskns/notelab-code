import mqtt_client
import http_client
import time
import json

# parameters
ip_server_http = "http://127.0.0.1:9200"
ip_broker_mqtt = "127.0.0.1"
topic_mqtt = "default_topic"

# connect to mqtt broker
mqttc = mqtt_client.connect(ip_broker_mqtt)

# keep checking if new data arrived
while True:
    payload = http_client.get_data(ip_server_http + "/_search")
    if payload is not None:
        mqttc.publish(topic_mqtt, json.dumps(payload))
    time.sleep(1)
