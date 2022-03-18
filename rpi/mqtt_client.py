import paho.mqtt.client as mqtt


def on_connect(client, userdata, flags, rc):
    print("MQTT client - connected to broker, code " + str(rc))


def on_message(client, userdata, msg):
    global message
    message = msg
    topic = msg.topic
    payload = str(msg.payload.decode("utf-8"))
    print("MQTT client - msg received [" + topic + "]: " + payload)


def on_subscribe(mqttc, obj, result, granted_qos):
    print("MQTT client - subscribed: " + str(result) + " " + str(granted_qos))


def on_publish(client, userdata, result):
    print("MQTT client - published:  " + str(result))


def on_log(mqttc, obj, level, string):
    print(string)


def connect(ip, port=1883):
    mqttc = mqtt.Client()
    mqttc.on_connect = on_connect
    mqttc.on_message = on_message
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe
    mqttc.on_log = on_log
    try:
        mqttc.connect(ip, port, 60) 
    except:
        print("MQTT client - [" + ip + ":" + str(port) + "] connection failed!, exiting...")
        exit(1)
    return mqttc


if __name__ == "__main__":
    mqtt_broker_ip = "broker.hivemq.com"
    mqtt_broker_port = 1883
    mqtt_topic = "testMQTT"
    mqttc = connect(mqtt_broker_ip, mqtt_broker_port)
    mqttc.subscribe(mqtt_topic)
    mqttc.loop_forever()