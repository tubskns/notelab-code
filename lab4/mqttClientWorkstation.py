import paho.mqtt.client as mqtt # Paho MQTT client

# parameters
MQTT_BROKER_IP="192.168.1.3" 
MQTT_BROKER_PORT=1883
MQTT_TOPIC = "WorkstationTest"

mqttClient = mqtt.Client() # create a new instance of MQTT client:

# check when request is accepted by the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
       print("Connected to MQTT Broker!")
    else:
       print("Failed to connect, return code %d\n", rc)
  
mqttClient.on_connect = on_connect
mqttClient.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60) # connect to the broker
  
# client receives message from broker
def on_message(client, userdata, msg):
    #convert payload from byte string to  UTF-8
    msg.payload = msg.payload.decode("utf-8")
    print("Topic is: " + msg.topic + ", received message: "+str(msg.payload))

mqttClient.on_message = on_message
print("Subscribing to topic", MQTT_TOPIC)
mqttClient.subscribe(MQTT_TOPIC) # subscribe to the topic

mqttClient.loop_forever()
