# Notelab: Network of Things Engineering Lab



## Arduino Uno

### Requirements
- Temperature sensor ([datasheet](https://www.velleman.eu/downloads/29/vma311_a4v01.pdf))
- Ultrasonic sensor([datasheet](https://joy-it.net/files/files/Produkte/SEN-US01/SEN-US01\%20Datasheet\%20(English).pdf))
- PIR sensor([datasheet](http://www.openplatform.cc/index.php/home/index/details/apiid/38))
- LEDs ([datasheet](https://asset.conrad.com/media10/add/160267/c1/-/en/001661532DS01/datenblatt-1661532-barthelme-led-sortiment-kaltweiss-warmweiss-gelb-blau-rot-gruen-rund-5-mm.pdf))
- Arduino Uno Wifi ([datasheet](https://asset.conrad.com/media10/add/160267/c1/-/en/001969870DS00/datenblatt-1969870-arduino-board-uno-wifi-rev2-core.pdf))

### Tools
- Arduino firmware ([source](https://github.com/arduino/nina-fw))
- Arduino firmware updater ([tutorial](https://docs.arduino.cc/tutorials/generic/firmware-updater))
- Arduino IDE ([tutorial](https://www.arduino.cc/en/Guide/Linux))

### Libraries
- LiquidCrystal_I2C - v1.1.4 ([source](https://github.com/johnrickman/LiquidCrystal_I2C))
- ...


## Raspberry Pi

### Requirements
- Raspberry Pi 4 ([datasheet](https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-product-brief.pdf))
- Ubuntu installation on Raspberry Pis ([tutorial](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi))

### Tools
- `docker` ([installation](https://docs.docker.com/engine/install/ubuntu/))
- (optional) `mosquitto-clients` ([package](https://packages.ubuntu.com/focal/mosquitto-clients))
- (optional) `amqp-tools` ([package](https://packages.ubuntu.com/focal/amqp-tools))

### Libraries
- `pip` ([installation](https://packaging.python.org/en/latest/tutorials/installing-packages/))
- `paho` ([installation](https://www.eclipse.org/paho/index.php?page=clients/python/index.php))
- `pika` ([installation](https://pika.readthedocs.io/en/stable/))
- `requests` ([installation](https://docs.python-requests.org/en/latest/user/install/))


## Server

### Requirements
- Ubuntu server installation ([tutorial](https://ubuntu.com/tutorials/install-ubuntu-server))
- `k3s` ([installation](https://rancher.com/docs/k3s/latest/en/installation/install-options/))
- `helm` ([installation](https://helm.sh/docs/intro/install/#from-script))


## Workstation

### Requirements
- Ubuntu desktop installation ([tutorial](https://ubuntu.com/tutorials/install-ubuntu-desktop))
- `ssh` ([installation](https://ubuntu.com/server/docs/service-openssh))
- `git` ([installation](https://git-scm.com/download/linux))
- `curl` ([installation](https://curl.se/download.html))

