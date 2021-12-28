import json
import mqtt_client
import http_client
import time


def process(url_http, previous_last_hit):
    payload = http_client.get_data(url_http)
    if payload is not None:
        hits = payload["hits"]["hits"]
        last_hit = hits[len(hits) - 1]
        if last_hit != previous_last_hit:
            msg = last_hit["_source"]
            msg_str = json.dumps(msg)
            if temp_topic_http in url_http:
                print("Forwarding message [" + temp_topic_http + "]: " + msg_str)
                mqttc.publish(temp_topic_mqtt, msg_str)
            elif dist_topic_http in url_http:
                print("Forwarding message [" + dist_topic_http + "]: " + msg_str)
                mqttc.publish(dist_topic_mqtt, msg_str)
            elif motion_topic_http in url_http:
                print("Forwarding message [" + motion_topic_http + "]: " + msg_str)
                mqttc.publish(motion_topic_mqtt, msg_str)
            return last_hit


# parameters
ip_server_http = "http://127.0.0.1:9200"
temp_topic_http = "temperature_topic"
dist_topic_http = "distance_topic"
motion_topic_http = "motion_topic"

ip_broker_mqtt = "127.0.0.1"
temp_topic_mqtt = "temperature_actuator_topic"
dist_topic_mqtt = "distance_actuator_topic"
motion_topic_mqtt = "motion_actuator_topic"

# connect to mqtt broker
mqttc = mqtt_client.connect(ip_broker_mqtt)

# keep checking if new data arrived
temp_last_hit = None
dist_last_hit = None
motion_last_hit = None
while True:
    temp_last_hit = process(
        ip_server_http + "/" + temp_topic_http + "/_search", temp_last_hit
    )
    dist_last_hit = process(
        ip_server_http + "/" + dist_topic_http + "/_search", dist_last_hit
    )
    motion_last_hit = process(
        ip_server_http + "/" + motion_topic_http + "/_search", motion_last_hit
    )
    time.sleep(0.5)
