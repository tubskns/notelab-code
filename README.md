# Notelab code (WIP)

This repository contains all the code required for the Notelab class. 

Structure:

```
.
├── LICENSE
├── microcontroller
│   ├── actuators
│   │   ├── distance
│   │   │   └── subscriber_HCSR04
│   │   │       └── subscriber_HCSR04.ino
│   │   ├── ext_led
│   │   │   └── ext_led.ino
│   │   ├── int_led
│   │   │   └── int_led.ino
│   │   ├── motion
│   │   │   └── subscriber_PIR
│   │   │       └── subscriber_PIR.ino
│   │   └── temperature
│   │       └── subscriber_DHT11
│   │           ├── mqtt_client.cpp -> ../../../mqtt_client/mqtt_client.cpp
│   │           ├── mqtt_client.h -> ../../../mqtt_client/mqtt_client.h
│   │           ├── subscriber_DHT11.ino
│   │           ├── wifi_connection.cpp -> ../../../wifi_connection/wifi_connection.cpp
│   │           └── wifi_connection.h -> ../../../wifi_connection/wifi_connection.h
│   ├── mqtt_client
│   │   ├── mqtt_client.cpp
│   │   ├── mqtt_client.h
│   │   ├── mqtt_client.ino
│   │   ├── wifi_connection.cpp -> ../wifi_connection/wifi_connection.cpp
│   │   └── wifi_connection.h -> ../wifi_connection/wifi_connection.h
│   ├── sensors
│   │   ├── distance
│   │   │   ├── interface_HCSR04
│   │   │   │   ├── interface_HCSR04.cpp
│   │   │   │   ├── interface_HCSR04.h
│   │   │   │   └── interface_HCSR04.ino
│   │   │   └── publisher_HCSR04
│   │   │       ├── interface_HCSR04.cpp -> ../interface_HCSR04/interface_HCSR04.cpp
│   │   │       ├── interface_HCSR04.h -> ../interface_HCSR04/interface_HCSR04.h
│   │   │       ├── mqtt_client.cpp -> ../../../mqtt_client/mqtt_client.cpp
│   │   │       ├── mqtt_client.h -> ../../../mqtt_client/mqtt_client.h
│   │   │       ├── publisher_HCSR04.ino
│   │   │       ├── wifi_connection.cpp -> ../../../wifi_connection/wifi_connection.cpp
│   │   │       └── wifi_connection.h -> ../../../wifi_connection/wifi_connection.h
│   │   ├── motion
│   │   │   ├── interface_PIR
│   │   │   │   ├── interface_PIR.cpp
│   │   │   │   ├── interface_PIR.h
│   │   │   │   └── interface_PIR.ino
│   │   │   └── publisher_PIR
│   │   │       └── publisher_PIR.ino
│   │   └── temperature
│   │       ├── interface_DHT11
│   │       │   ├── interface_DHT11.cpp
│   │       │   ├── interface_DHT11.h
│   │       │   └── interface_DHT11.ino
│   │       └── publisher_DHT11
│   │           ├── interface_DHT11.cpp -> ../interface_DHT11/interface_DHT11.cpp
│   │           ├── interface_DHT11.h -> ../interface_DHT11/interface_DHT11.h
│   │           ├── mqtt_client.cpp -> ../../../mqtt_client/mqtt_client.cpp
│   │           ├── mqtt_client.h -> ../../../mqtt_client/mqtt_client.h
│   │           ├── publisher_DHT11.ino
│   │           ├── wifi_connection.cpp -> ../../../wifi_connection/wifi_connection.cpp
│   │           └── wifi_connection.h -> ../../../wifi_connection/wifi_connection.h
│   └── wifi_connection
│       ├── wifi_connection.cpp
│       ├── wifi_connection.h
│       └── wifi_connection.ino
├── README.md
├── rpi
│   ├── amqp_pub.py
│   ├── http_client.py
│   ├── mqtt_amqp_connector.py
│   └── mqtt_sub.py
└── server
    ├── deploy_helper.sh
    ├── notelab.yml
    └── utils.sh
```

