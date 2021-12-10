import mqtt_sub
import amqp_pub


def run(
    ip_rabbitmq,
    ip_broker_mqtt,
    port_rabbitmq=5672,
    user_rabbitmq="user",
    pass_rabbitmq="password",
    queue_rabbitmq="notelab",
    port_broker_mqtt=1883,
    topics_mqtt="default_topic",
):

    # connect to rabbitmq
    amqp_channel = amqp_pub.connect_to_rabbitmq(
        ip_rabbitmq, port_rabbitmq, user_rabbitmq, pass_rabbitmq, queue_rabbitmq
    )
    # connect to mqtt broker and subscribe to topics
    mqttc = mqtt_sub.connect_to_mqtt_broker(ip_broker_mqtt, port_broker_mqtt)
    mqttc.on_message = mqtt_sub.on_message
    mqttc.subscribe(topics_mqtt)
    # start mqtt loop
    mqttc.loop_start()

    return amqp_channel


if __name__ == "__main__":
    ip_rabbitmq = "127.0.0.1"
    ip_broker_mqtt = "127.0.0.1"
    mqtt_sub.message = None
    amqp_channel = run(ip_rabbitmq, ip_broker_mqtt)
    while True:
        if mqtt_sub.message is not None:
            amqp_pub.send_message_to_rabbitmq(
                amqp_channel,
                mqtt_sub.message,
            )
            mqtt_sub.message = None
