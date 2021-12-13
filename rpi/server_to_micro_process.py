import json
import mqtt_client
import http_client
import time


def process(url_http, topic_mqtt):
    payload = http_client.get_data(url_http)
    if payload is not None:
        for value in payload["hits"]["hits"]:
            value = value["_source"]
            # TO-DO processing
            if topic_mqtt is temp_topic:
                print(json.dumps(value))
                # TO-DO processing
            elif topic_mqtt is dist_topic:
                print(json.dumps(value))
                # TO-DO processing
            elif topic_mqtt is motion_topic:
                print(json.dumps(value))
                # TO-DO processing
            mqttc.publish(topic_mqtt, json.dumps(value))


# parameters
ip_server_http = "http://127.0.0.1:9200"
ip_broker_mqtt = "127.0.0.1"
temp_topic = "temperature_topic"
dist_topic = "distance_topic"
motion_topic = "motion_topic"

# connect to mqtt broker
mqttc = mqtt_client.connect(ip_broker_mqtt)

# keep checking if new data arrived
while True:
    process(ip_server_http + "/" + temp_topic + "/_search", temp_topic)
    process(ip_server_http + "/" + dist_topic + "/_search", dist_topic)
    process(ip_server_http + "/" + motion_topic + "/_search", motion_topic)
    time.sleep(1)
