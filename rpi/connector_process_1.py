import mqtt_client
import amqp_client
import json, time

# rabbit
ip_rabbit = "192.168.1.7"
exchange_rabbit = "amq.topic"
temp_r_key_rabbit = "notelab"
temp_queue_rabbit = "notelab"
dist_r_key_rabbit = "dist_rabbit"
dist_queue_rabbit = "dist_rabbit"
motion_r_key_rabbit = "motion_rabbit"
motion_queue_rabbit = "motion_rabbit"

# mosquitto
ip_mosquitto = "192.168.1.3"
temp_topic = "temp_topic"
dist_topic = "dist_topic"
motion_topic = "motion_topic"
topics_mosquitto = [
    (temp_topic, 1),
    (dist_topic, 1),
    (motion_topic, 1),
]

# connect to rabbitmq
amqp_channel = amqp_client.connect_to_broker(
    ip_rabbit, port=5672, user="user", passw="password"
)

# connect to mosquitto and subscribe to topics
mqtt_client.message = None
mqttc = mqtt_client.connect(ip_mosquitto)
mqttc.subscribe(topics_mosquitto)
last_payload = None

# global vars
is_activated = False
activation_interval = 25
start_time = 100000000
temp_values = []


mqttc.loop_start()
while True:
    if mqtt_client.message is not None:
        
        topic = mqtt_client.message.topic 
        msg = json.loads(str(mqtt_client.message.payload.decode("utf-8")))

        if topic == motion_topic: # check to activate workflow based on motion
            if msg["motion"]:
                if not is_activated: # activate circuit
                    is_activated = True
                    start_time = time.time()
                    amqp_client.publish(amqp_channel, json.dumps(msg), exchange_rabbit, motion_r_key_rabbit, motion_queue_rabbit)
            else:
                elapsed_time = time.time() - start_time
                if elapsed_time > activation_interval: # deactivate circuit
                    amqp_client.publish(amqp_channel, json.dumps(msg), exchange_rabbit, motion_r_key_rabbit, motion_queue_rabbit)
                    is_activated = False
                    
        if topic == temp_topic: # calculate avg temp of x values and send
            if len(temp_values) < 24:
                temp_values.append(msg["temperature"])
            else:
                avg_temp = sum(temp_values) / len(temp_values)
                msg["temperature"] = avg_temp
                amqp_client.publish(amqp_channel, json.dumps(msg), exchange_rabbit, temp_r_key_rabbit, temp_queue_rabbit)
                temp_values = []

        elif topic == dist_topic:
            if is_activated:
                amqp_client.publish(amqp_channel, json.dumps(msg), exchange_rabbit, dist_r_key_rabbit, dist_queue_rabbit)     

        mqtt_client.message = None # reset message
