import pika


def publish(channel, msg, exchange="amq.topic", routing_key="logstash"):
    channel.basic_publish(exchange=exchange, routing_key=routing_key, body=msg)
    print("AMQP publisher - Message sent: " + msg)


def connect_to_broker(ip, port=5672, user="user", passw="password", queue="notelab"):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/", credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    channel.queue_declare(queue=queue, durable=True)  # queue to send data
    return channel

def on_message(channel, method, properties, msg):
    global message
    message = msg
    print("AMQP consumer - Message receieved: " + msg.decode("utf-8"))

def subscribe(channel, queue):
    channel.basic_consume(queue, on_message_callback=on_message, auto_ack=True)
    channel.start_consuming()
    print("AMQP subscriber - Subscribed to: " + queue)

if __name__ == "__main__":
    #  server parameters - RabbitMq
    ip = "192.168.1.7"  # server IP address
    port = 5672  #
    user = "user"
    passw = "password"
    queue = "notelab"
    exchange = "amq.topic"
    routing_key = "test"
    message = "test_amqp_message"
    channel = connect_to_broker(ip, port, user, passw, queue)
    publish(channel, message, exchange, routing_key)
    print("Message sent to RabbitMQ: " + message)
    subscribe(channel, queue)
    print("Message received from RabbitMQ: " + message)
  