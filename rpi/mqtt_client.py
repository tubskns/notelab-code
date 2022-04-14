import paho.mqtt.client as mqtt
import logging

def on_connect(client, userdata, flags, rc):
    logging.info("MQTT - connected to broker, code " + str(rc))


def on_message(client, userdata, msg):
    global message
    message = msg
    topic = msg.topic
    payload = str(msg.payload.decode("utf-8"))
    logging.debug("MQTT - msg received [" + topic + "]: " + payload)


def on_subscribe(client, userdata, mid, granted_qos):
    logging.info("MQTT - subscribed: " + str(mid) + " " + str(granted_qos))


def on_publish(client, userdata, mid):
    logging.debug("MQTT - published:  " + str(mid))


def on_log(client, userdata, level, string):
    logging.debug(string)


def connect(ip, port=1883):
    mqttc = mqtt.Client()
    mqttc.on_connect = on_connect
    mqttc.on_message = on_message
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe
    # mqttc.on_log = on_log
    try:
        mqttc.connect(ip, port, 60) 
    except:
        logging.error("MQTT - [" + ip + ":" + str(port) + "] connection failed!, exiting...")
        exit(1)
    return mqttc


if __name__ == "__main__":
    mqtt_broker_ip = "192.168.1.3"
    mqtt_broker_port = 1883
    mqtt_topic = "testMQTT"
    mqttc = connect(mqtt_broker_ip, mqtt_broker_port)
    mqttc.subscribe(mqtt_topic)
    mqttc.loop_forever()