# Notelab: Network of Things Engineering Lab


## Arduino Uno

### Requirements
- DHT11 sensor ([datasheet](https://www.velleman.eu/downloads/29/vma311_a4v01.pdf))
- HC-SR04 sensor([datasheet](https://joy-it.net/files/files/Produkte/SEN-US01/SEN-US01\%20Datasheet\%20(English).pdf))
- PIR sensor([datasheet](http://www.openplatform.cc/index.php/home/index/details/apiid/38))
- LEDs ([datasheet](https://asset.re-in.de/add/160267/c1/-/en/001661532DS01/DA_Barthelme-LED-Sortiment-Kaltweiss-Warmweiss-Gelb-Blau-Rot-Gruen-Rund-5mm.pdf))
- 16x2 LCD ([datasheet](https://joy-it.net/files/files/Produkte/SBC-LCD16x2/SBC-LCD16x2_Manual_2021-04-07.pdf))
- Arduino Uno Wifi rev2 ([datasheet](https://content.arduino.cc/assets/Pinout-UNOwifirev2_latest.pdf))
- Arduino firmware ([source](https://github.com/arduino/nina-fw)), firmware updater ([tutorial](https://docs.arduino.cc/tutorials/generic/firmware-updater))
  
### Libraries
- DHT11 lib v1.4.3 ([source](https://github.com/adafruit/DHT-sensor-library))
- LiquidCrystal_I2C lib v1.1.2 ([source](https://github.com/johnrickman/LiquidCrystal_I2C))
- WiFiNINA lib v1.8.13 ([source](https://github.com/arduino-libraries/WiFiNINA))
- MQTT lib v2.5.0 ([source](https://github.com/256dpi/arduino-mqtt))
- JSON lib v6.19.4 ([source](https://github.com/bblanchon/ArduinoJson))




## Raspberry Pi

### Requirements
- Raspberry Pi 4 ([datasheet](https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-product-brief.pdf))
- Ubuntu server 20.04 ARM ([installation](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi))
- Python v3.9 ([installation](https://www.python.org/downloads/))
- pip v20.3.4 ([installation](https://packaging.python.org/en/latest/tutorials/installing-packages/))

### Libraries
- paho v1.6.1 ([installation](https://www.eclipse.org/paho/index.php?page=clients/python/index.php))
- pika v1.2.1 ([installation](https://pika.readthedocs.io/en/stable/))
- requests v2.25.1 ([installation](https://docs.python-requests.org/en/latest/user/install/))

### Tools
- Docker v20.10.8 ([installation](https://docs.docker.com/engine/install/ubuntu/))
- Mosquitto v1.6.15 ([docker image](https://hub.docker.com/_/eclipse-mosquitto))




## Server

### Requirements
- Ubuntu server 20.04 ([installation](https://ubuntu.com/tutorials/install-ubuntu-server))
- git v2.34.1 ([installation](https://git-scm.com/download/linux))
- helm v1.20.9 ([installation](https://helm.sh/docs/intro/install/#from-script))

### Tools

- K3s v1.20.9+k3s1 ([installation](https://rancher.com/docs/k3s/latest/en/installation/install-options/))
- RabbitMQ v3.10.5 ([homepage](https://www.rabbitmq.com/)), helm chart v.10.1.14 ([source](https://github.com/bitnami/charts/tree/master/bitnami/rabbitmq))
- Logstash v7.17.3 ([homepage](https://www.elastic.co/logstash/)), helm chart v7.17.3 ([source](https://github.com/elastic/helm-charts/tree/7.17/logstash))
- Elasticsearch v7.17.3 ([homepage](https://www.elastic.co/elasticsearch/)), helm chart v7.17.3 ([source](https://github.com/elastic/helm-charts/tree/7.17/elasticsearch))




## Workstation

### Requirements
- Ubuntu desktop 20.04 ([installation](https://ubuntu.com/tutorials/install-ubuntu-desktop))
- git v2.34.1 ([installation](https://git-scm.com/download/linux))
- Arduino IDE v1.8.13 ([tutorial](https://www.arduino.cc/en/Guide/Linux))

### Tools

- curl v7.81.0 ([installation](https://curl.se/download.html))
- mosquitto-clients v.2.0.10 ([package](https://packages.ubuntu.com/focal/mosquitto-clients))
- amqp-tools v.0.10.0-1 ([package](https://packages.ubuntu.com/focal/amqp-tools))