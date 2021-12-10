#!/bin/bash
# Brendan Creane
# Block until a pod specified by a selector is "ready"
# or a timeout occurs.

#
# podStatus() - takes a selector as argument, e.g. "k8s-app=kube-dns"
# and returns the pod "ready" status as a bool string ("true"). Note that if
# the pod is in the "pending" state, there is no containerStatus yet, so
# podStatus() returns an empty string. Success means seeing the "true"
# substring, but failure can be "false" or an empty string.
#
function podStatus() {
  local label="$1"
  local status=$(kubectl get pods --selector="${label}" -o json --all-namespaces | jq -r '.items[] | .status.containerStatuses[]? | [.name, .image, .ready|tostring] |join(":")')
  echo "${status}"
}

#
# blockUntilPodIsReady() - takes a pod selector and a timeout in seconds
# as arguements. If the pod never stabilizes, bail. Otherwise return as
# soon as the pod is "ready."
#
function blockUntilPodIsReady() {
  local label="$1"
  local secs="$2"

  echo -n "Waiting for \"${label}\" to be ready: "
  until [[ $(podStatus "${label}") =~ "true" ]]; do
    if [ "$secs" -eq 0 ]; then
      echo "\"${label}\" never stabilized."
      exit 1
    fi

    : $((secs--))
    echo -n .
    sleep 1
  done
}

function waitUntilK3sIsReady() {
  local secs="$1"
  STATUS_CMD="sudo kubectl cluster-info"
  until $STATUS_CMD; do
    $STATUS_CMD
    if [ "$secs" -eq 0 ]; then
      echo "k3s could not be deployed"
      exit 1
    fi

    : $((secs--))
    echo -n .
    sleep 1
  done
}
