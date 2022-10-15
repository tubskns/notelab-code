module Variables
    $IMAGE = "generic/ubuntu2004"
    $NUM_VMS = 4
    $MEM = "6144"
    $CPU = "3"
    $GUEST_PORTS = [30672, 31672, 32200] # [rabbitmq, rabbitmq (admin), elasticsearch]
    $HOST_PORTS = [60010, 60011, 60012,
                   60020, 60021, 60022,
                   60030, 60031, 60032,
                   60040, 60041, 60042]
end
