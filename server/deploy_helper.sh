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

usage='Usage:
'$0' [OPTION]
OPTIONS:
-r \t deploys rabbitmq.
-e \t deploys elasticsearch.
-l \t deploys logstash.
-u \t uninstalls everything.
'
rabbitmq=false
elasticsearch=false
logstash=false

while getopts "relu" opt; do
    case $opt in
    r)
        rabbitmq=true
        ;;
    e)
        elasticsearch=true
        ;;
    l)
        logstash=true
        ;;
    u) 
        /usr/local/bin/k3s-uninstall.sh
        exit 0
        ;;
    *)
        echo -e "Invalid option $1 \n\n${usage}"
        exit 0
        ;;
    esac
done

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

# deploy k3s
export DEV_NS=default
if hash sudo kubectl 2>/dev/null; then
    sudo cp /etc/rancher/k3s/k3s.yaml ~/.kube/k3s-config && sudo chown $USER: ~/.kube/k3s-config && export KUBECONFIG=~/.kube/k3s-config
else
    log "INFO" "installing k3s..."
    curl -sfL https://get.k3s.io | INSTALL_K3S_VERSION=v1.20.9+k3s1 sh -
    log "INFO" "waiting for k3s to start..."
    sleep 30
    waitUntilK3sIsReady $TIMER
    rm -rf ~/.kube && mkdir ~/.kube
    sudo cp /etc/rancher/k3s/k3s.yaml ~/.kube/k3s-config && sudo chown $USER: ~/.kube/k3s-config && export KUBECONFIG=~/.kube/k3s-config
    log "INFO" "done"
fi

# deploy selected tools
if [[ "$rabbitmq" = true ]]; then
    log "INFO" "deploying rabbitMQ..."
    helm repo add bitnami https://charts.bitnami.com/bitnami
    helm repo update
    helm install rabbitmq bitnami/rabbitmq --namespace $DEV_NS \
        --version 10.1.14 \
        --set replicaCount=1 \
        --set auth.username=user,auth.password=password \
        --set service.type=NodePort,service.nodePorts.amqp=30672,service.nodePorts.manager=31672
    log "INFO" "done"
fi
if [ "$elasticsearch" = true ]; then
    log "INFO" "deploying elasticsearch..."
    helm repo add elastic https://Helm.elastic.co
    helm install elasticsearch elastic/elasticsearch --namespace $DEV_NS \
        --version 7.17.1 \
        --set replicas=1 \
        --set service.type=NodePort,service.nodePort=32200
    log "INFO" "done"
fi
if [ "$logstash" = true ]; then
    log "INFO" "deploying logstash using notelab.yml file..."
    helm install logstash-notelab elastic/logstash --namespace $DEV_NS \
        --version 7.17.1 \
        --set replicas=1 \
        -f notelab.yml 
    log "INFO" "done"
fi

# wait for deployment
if [[ "$rabbitmq" = true ]]; then
    blockUntilPodIsReady "app.kubernetes.io/name=rabbitmq" $TIMER
    log "INFO" "done"
fi
if [ "$elasticsearch" = true ]; then
    blockUntilPodIsReady "app=elasticsearch-master" $TIMER
    log "INFO" "done"
fi
if [ "$logstash" = true ]; then
    blockUntilPodIsReady "app=logstash-notelab-logstash" $TIMER
    log "INFO" "done"
fi

