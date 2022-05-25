module Variables
    $IMAGE = "generic/ubuntu2004"
    $NUM_VMS = 2
    $MEM = "8192"
    $CPU = "3"
    $GUEST_PORTS = [5672, 15672, 9200] # [rabbitmq, rabbitmq, elasticsearch]
    $HOST_PORTS = [60000, 60001, 60002,
                   60010, 60011, 60012,
                   60020, 60021, 60022]
end
