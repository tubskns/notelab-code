## Mosquitto 

### Install

```shell
docker run -it -p 1883:1883 eclipse-mosquitto:1.6.15
```

### Test

```shell
mosquitto_sub -h localhost -t "notelab/test"
```

```shell
mosquitto_pub -h localhost -t "notelab/test" -m "Testing the MQTT communication"
```