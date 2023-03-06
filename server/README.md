## Server

### k3s Install 

```shell
curl -sfL https://get.k3s.io | INSTALL_K3S_VERSION=v1.20.9+k3s1 sh -
```

### k3s list pods 

```shell
kubectl get pods -A
```

### k3s fix permissions

To fix `k3s` permissions, run the following command (or add it to your `.bashrc` or `.zshrc`):

```shell
sudo cp /etc/rancher/k3s/k3s.yaml ~/.kube/k3s-config && sudo chown $USER: ~/.kube/k3s-config && export KUBECONFIG=~/.kube/k3s-config
```

### k3s uninstall

```shell
/usr/local/bin/k3s-uninstall.sh
```

### RabbitMQ install

```shell
helm repo add bitnami https://charts.bitnami.com/bitnami
helm repo update
helm install rabbitmq bitnami/rabbitmq --version 10.1.14 \
    --set replicaCount=1 \
    --set auth.username=user,auth.password=password \
    --set service.type=NodePort,service.nodePorts.amqp=30672,service.nodePorts.manager=31672
```

### RabbitMQ test

```shell
amqp-consume --url amqp://user:password@SERVER_IP:30672 -e amq.topic -r test cat
```

```shell
amqp-publish --url amqp://user:password@SERVER_IP:30672 -e amq.topic -r test -b Testing_AMQP_communication
```



### Elasticsearch install

```shell
helm repo add elastic https://Helm.elastic.co
helm repo update
helm install elasticsearch elastic/elasticsearch \
    --version 7.17.1 \
    --set replicas=1 \
    --set service.type=NodePort,service.nodePort=32200
```

### Elasticsearch test

```shell
curl -H "Content-Type: application/json" -XPOST "http://SERVER_IP:32200/notelab/temperature_topic/1" -d ’{"id":"test", "temperature":22}’
```

```shell
curl -XGET "http://SERVER_IP:32200/notelab/_search?pretty" -H 'Content-Type: application/json' -d '{"query": {"match_all": {}}}'
```


### Logstash install

```shell
helm repo add elastic https://Helm.elastic.co
helm repo update
helm install logstash-notelab elastic/logstash \
    --version 7.17.1 \
    --set replicas=1 \
    -f logstash_conf.yml 
```

