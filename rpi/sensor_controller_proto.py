import mqtt_client
import amqp_client

# rabbit
ip_rabbit = "SERVER_IP"
port_rabbit = 30672
user_rabbit = "user"
pass_rabbit = "password"
exchange_rabbit = "amq.topic"
r_key_rabbit = "control_sensor_key"
queue_rabbit = "control_sensor_queue"
# mosquitto
ip_mosquitto = "MQTT_BROKER_IP"
topic_mosquitto = "test_topic"

# connect to rabbitmq
amqp_ch = amqp_client.connect_to_broker(ip_rabbit, port=port_rabbit, user=user_rabbit, passw=pass_rabbit)
amqp_client.create_queue(amqp_ch, exchange_rabbit, r_key_rabbit, queue_rabbit)

# connect to mosquitto and subscribe to topics
mqtt_client.message = None
mqttc = mqtt_client.connect(ip_mosquitto)
mqttc.subscribe(topic_mosquitto)

# keep checking if new data arrived
mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        # retrieve topic and payload
        topic = mqtt_client.message
        payload = str(mqtt_client.message.payload.decode("utf-8"))
        print("sensor-controller - MQTT subscriber - Message received: " + payload)
        # forward payload to amqp server
        print("sensor-controller - AMQP publisher - Forwarding data from Mosquitto to Rabbitmq: " + payload)
        amqp_ch.basic_publish(exchange_rabbit, r_key_rabbit, payload)
        # reset message
        mqtt_client.message = None
