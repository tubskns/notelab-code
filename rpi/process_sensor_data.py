import mqtt_amqp_connector as conn
import amqp_pub
import mqtt_sub


def process_temp(data):
    return data


def process_dist(data):
    return data


def process_motion(data):
    return data


if __name__ == "__main__":
    ip_rabbitmq = "127.0.0.1"
    ip_broker_mqtt = "127.0.0.1"
    temp_topic = "temperature_topic"
    dist_topic = "distance_topic"
    motion_topic = "motion_topic"
    topics_mqtt = [
        (temp_topic, 1),
        (dist_topic, 1),
        (motion_topic, 1),
    ]
    mqtt_sub.message = None
    amqp_channel = conn.run(ip_rabbitmq, ip_broker_mqtt)
    while True:
        if mqtt_sub.message is not None:
            amqp_pub.send_message_to_rabbitmq(
                amqp_channel,
                mqtt_sub.message,
            )
            mqtt_sub.message = None
