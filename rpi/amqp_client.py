import pika
import logging


def connect_to_broker(ip, port, user, passw):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/", credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    logging.info("AMQP - Connected to broker: " + str(ip) + ":" + str(port))
    return channel


def create_queue(channel, exchange, routing_key, queue):
    channel.queue_declare(queue=queue, durable=True)
    channel.queue_bind(exchange=exchange, queue=queue, routing_key=routing_key)
    logging.debug("AMQP - Queue declare and bind: " + queue)


def on_message(channel, method, properties, msg):
    logging.debug("AMQP - Message received: " + msg.decode("utf-8"))


def subscribe(channel, queue, on_message_callback):
    channel.basic_consume(queue, on_message_callback=on_message_callback)
    logging.info("AMQP - Subscribed to: " + queue)


if __name__ == "__main__":
    logging.basicConfig(
        format="%(asctime)s | %(name)s | %(levelname)s | %(message)s",
        level=logging.DEBUG,
    )
    ip = "SERVER_IP"
    port = 5672
    user = "user"
    passw = "password"
    queue = "queue_test"
    exchange = "amq.topic"
    routing_key = "routing_key_test"
    message = "message_test"
    channel = connect_to_broker(ip, port, user, passw)
    create_queue(channel, exchange, routing_key, queue)
    channel.basic_publish(exchange=exchange, routing_key=routing_key, body=message)
    subscribe(channel, queue, on_message)
    channel.start_consuming()
