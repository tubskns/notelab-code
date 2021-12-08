import pika

def send_message_to_rabbitmq(channel, exchange, routing_key, msg):
    channel.basic_publish(exchange=exchange, routing_key=routing_key, body=msg)

def connect_to_rabbitmq(ip, port, user, passw, queue):
    credentials = pika.PlainCredentials(user, passw)
    parameters = pika.ConnectionParameters(ip, port, "/", credentials)
    connection = pika.BlockingConnection(parameters)
    channel = connection.channel()
    channel.queue_declare(queue=queue, durable=True)  # queue to send data
    return channel

if __name__ == "__main__":
    #  server parameters - RabbitMq
    ip = "192.168.1.7" #server IP address
    port = 5672   #
    user = "user"  
    passw = "password"
    queue = "notelab"

    exchange = "amq.topic"
    routing_key = "logstash"

    message = "test_amqp_message"

    channel = connect_to_rabbitmq(ip, port, user, passw, queue)
    send_message_to_rabbitmq(channel, exchange, routing_key, message)
    print("Message sent to RabbitMQ server: " + message)
