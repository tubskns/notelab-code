import paho.mqtt.client as mqtt
import pika

# connection with RabitMQ server
amqp_credentials = pika.PlainCredentials('user', 'password')
amqp_parameters = pika.ConnectionParameters('192.168.1.7', 5672, '/', amqp_credentials)
amqp_connection = pika.BlockingConnection(amqp_parameters)
channel = amqp_connection.channel() 
channel.queue_declare(queue='notelab', durable=True) # queue to send data

# MQTT broker parameters
MQTT_BROKER_IP="192.168.1.3"
MQTT_BROKER_PORT=1883
MQTT_TOPIC = "notelab/temperature&humidity"


mqttClient = mqtt.Client() #create s new instance of MQTT client
mqttMessage = ''

# check when request is accepted by the broker:
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

mqttClient.on_connect = on_connect
mqttClient.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60) #connect to the broker


# client receives message from broker
def on_message(client, userdata, msg):
    msg.payload = msg.payload.decode("utf-8")  #convert payload from byte string to  UTF-8
    mqttMessage=str(msg.payload)
    print ("MQTT topic is: " + msg.topic + ", and message received from MQTT broker: " + mqttMessage)
    send_message_to_rabbitmq(mqttMessage)


# forward the message from MQTT broker to RabbitMQ server
def send_message_to_rabbitmq(message):
    channel.basic_publish(exchange='amq.topic', routing_key='logstash', body = message)
    print("Message sent to RabbitMQ server: " + message)


mqttClient.on_message = on_message
print("Subscribing to topic",MQTT_TOPIC)
mqttClient.subscribe(MQTT_TOPIC) # subscribe to the topic

mqttClient.loop_forever()


