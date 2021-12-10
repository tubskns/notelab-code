#!/bin/bash

source utils.sh

###############################################################################
# Author	:	Francisco Carpio
# Github	:	https://github.com/fcarp10
###############################################################################
#   DO NOT JUST RUN THIS. EXAMINE AND JUDGE. RUN AT YOUR OWN RISK.
###############################################################################

TIMER=480

BLUE='\033[0;34m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
RED='\033[0;31m'
NO_COLOR='\033[0m'

function log() {
    if [[ $1 == "INFO" ]]; then
        printf "${BLUE}INFO:${NO_COLOR} %s \n" "$2"
    elif [[ $1 == "DONE" ]]; then
        printf "${GREEN}SUCCESS:${NO_COLOR} %s \n" "$2"
    elif [[ $1 == "WARN" ]]; then
        printf "${ORANGE}WARNING:${NO_COLOR} %s \n" "$2"
    else
        printf "${RED}FAILED:${NO_COLOR} %s \n" "$2"
    fi
}

log "INFO" "checking tools..."
command -v curl >/dev/null 2>&1 || {
    log "ERROR" "curl not found, aborting."
    exit 1
}
command -v jq >/dev/null 2>&1 || {
    log "ERROR" "jq not found, aborting."
    exit 1
}
command -v nc >/dev/null 2>&1 || {
    log "ERROR" "nc (netcat) not found, aborting."
    exit 1
}
command -v helm >/dev/null 2>&1 || {
    log "WARN" "helm not found, installing..."
    curl -sSLf https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3 | bash
}
log "DONE" "tools already installed"

####### k3s #######
log "INFO" "installing k3s..."
curl -sfL https://get.k3s.io | INSTALL_K3S_VERSION=v1.20.9+k3s1 sh -
log "INFO" "waiting for k3s to start..."
waitUntilK3sIsReady $TIMER
mkdir ~/.kube
sudo cp /etc/rancher/k3s/k3s.yaml ~/.kube/k3s-config && sudo chown $USER: ~/.kube/k3s-config && export KUBECONFIG=~/.kube/k3s-config
log "INFO" "done"

export DEV_NS=default

###################
##### deploy ######
###################
log "INFO" "deploying rabbitMQ..."
helm repo add groundhog2k https://groundhog2k.github.io/helm-charts/
helm install rabbitmq groundhog2k/rabbitmq --version 0.2.19 --namespace $DEV_NS --set replicaCount=1 --set authentication.user=user --set authentication.password=password
log "INFO" "done"
log "INFO" "deploying elasticsearch..."
helm repo add elastic https://Helm.elastic.co
helm install elasticsearch elastic/elasticsearch --namespace $DEV_NS --set replicas=1
log "INFO" "done"
log "INFO" "deploying kibana..."
helm repo add elastic https://Helm.elastic.co
helm install kibana elastic/kibana --namespace $DEV_NS --set replicas=1
log "INFO" "done"
log "INFO" "deploying logstash using notelab.yml file..."
helm install logstash-notelab elastic/logstash --namespace $DEV_NS -f notelab.yml --set replicas=1
log "INFO" "done"

################################
##### wait for deployment ######
################################
blockUntilPodIsReady "app.kubernetes.io/name=rabbitmq" $TIMER
blockUntilPodIsReady "app=elasticsearch-master" $TIMER
blockUntilPodIsReady "app=kibana" $TIMER
blockUntilPodIsReady "app=logstash-notelab-logstash" $TIMER
log "INFO" "done"

#########################
##### port-forward ######
#########################
kubectl port-forward -n $DEV_NS svc/rabbitmq --address 0.0.0.0 5672 &
kubectl port-forward -n $DEV_NS svc/rabbitmq --address 0.0.0.0 15672:15672 &
ES_POD=$(kubectl get pods -n $DEV_NS -l "app=elasticsearch-master" -o jsonpath="{.items[0].metadata.name}")
kubectl port-forward -n $DEV_NS $ES_POD --address 0.0.0.0 9200 &
KIBANA_POD=$(kubectl get pods -n $DEV_NS -l "app=kibana" -o jsonpath="{.items[0].metadata.name}")
kubectl port-forward -n $DEV_NS $KIBANA_POD --address 0.0.0.0 5601:5601 &
log "INFO" "done"

###################################
##### keep connections alive ######
###################################
log "INFO" "keeping connections alive..."
while true; do
    nc -vz 127.0.0.1 5672
    nc -vz 127.0.0.1 15672
    nc -vz 127.0.0.1 9200
    nc -vz 127.0.0.1 5601
    sleep 60
done
