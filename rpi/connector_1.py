import mqtt_client, amqp_client

# rabbit
ip_rabbit = "192.168.1.7"
exchange_rabbit = "amq.topic"
r_key_rabbit = "notelab"
queue_rabbit = "notelab"
# mosquitto
ip_mosquitto = "192.168.1.3"
topic_mosquitto = "test_topic"

# connect to rabbitmq
amqp_channel = amqp_client.connect_to_broker(
    ip_rabbit, port=5672, user="user", passw="password"
)
amqp_client.create_queue(amqp_channel, exchange_rabbit, r_key_rabbit, queue_rabbit)

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
        print("Connector_1 - MQTT subscriber - Message received: " + payload)
        # forward payload to amqp server
        print(
            "Connector_1 - AMQP publisher - Forwarding data from Mosquitto to Rabbitmq: "
            + payload
        )
        amqp_channel.basic_publish(
            exchange=exchange_rabbit, routing_key=r_key_rabbit, body=payload
        )
        # reset message
        mqtt_client.message = None
