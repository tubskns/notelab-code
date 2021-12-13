import pika


def send_message_to_rabbitmq(
    channel, msg, exchange="amq.topic", routing_key="logstash"
):
    channel.basic_publish(exchange=exchange, routing_key=routing_key, body=msg)
    print("RabbitMQ publisher - Message sent: " + msg)


def connect_to_rabbitmq(ip, port=5672, user="user", passw="password", queue="notelab"):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/", credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    channel.queue_declare(queue=queue, durable=True)  # queue to send data
    return channel


if __name__ == "__main__":
    #  server parameters - RabbitMq
    ip = "192.168.1.7"  # server IP address
    port = 5672  #
    user = "user"
    passw = "password"
    queue = "notelab"

    exchange = "amq.topic"
    routing_key = "logstash"

    message = "test_amqp_message"

    channel = connect_to_rabbitmq(ip, port, user, passw, queue)
    send_message_to_rabbitmq(channel, message, exchange, routing_key)
    print("Message sent to RabbitMQ server: " + message)
