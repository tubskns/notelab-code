import pika

def connect_to_broker(ip, port, user, passw):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/", credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    return channel


def publish(channel, msg, exchange, routing_key, queue):
    channel.queue_declare(queue=queue, durable=True)
    channel.queue_bind(exchange=exchange, queue=queue, routing_key=routing_key)
    channel.basic_publish(exchange=exchange, routing_key=routing_key, body=msg)
    print("AMQP publisher - Message sent: " + msg)


def on_message(channel, method, properties, msg):
    global message
    message = msg
    print("AMQP consumer - Message received: " + msg.decode("utf-8"))


def subscribe(channel, queue):
    channel.basic_consume(queue, on_message_callback=on_message, auto_ack=True)
    print("AMQP subscriber - Subscribed to: " + queue)
    channel.start_consuming()


if __name__ == "__main__":
    ip = "192.168.1.7"
    port = 5672
    user = "user"
    passw = "password"
    queue = "queue_test"
    exchange = "amq.topic"
    routing_key = "routing_key_test"
    message = "message_test"
    channel = connect_to_broker(ip, port, user, passw)
    publish(channel, message, exchange, routing_key, queue)
    subscribe(channel, queue)
