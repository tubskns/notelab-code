import paho.mqtt.client as mqtt  # Paho MQTT client

# parameters
MQTT_BROKER_IP = "192.168.1.3"
MQTT_BROKER_PORT = 1883
MQTT_TOPIC = "lab4"


# callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))


# callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload.decode("utf-8")))


def on_subscribe(mqttc, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


def on_log(mqttc, obj, level, string):
    print(string)


mqttc = mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.on_subscribe = on_subscribe
# Uncomment to enable debug messages
# mqttc.on_log = on_log

mqttc.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60)  # connect to the broker
mqttc.subscribe(MQTT_TOPIC)  # subscribe to the topic

mqttc.loop_forever()
