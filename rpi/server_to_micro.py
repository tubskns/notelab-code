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
prev_last_hit = None
while True:
    payload = http_client.get_data(ip_server_http + "/" + topic_mqtt + "/_search")
    if payload is not None:
        hits = payload["hits"]["hits"]
        last_hit = hits[len(hits) - 1]
        if last_hit != prev_last_hit:
            msg = last_hit["_source"]
            msg_str = json.dumps(msg)
            print("Forwarding message [" + topic_mqtt + "]: " + msg_str)
            mqttc.publish(topic_mqtt, msg_str)
            prev_last_hit = last_hit
    time.sleep(1)
