#!/bin/bash

. config.sh

sub() {
    local topic=$1
    echo "Listen for events on topic $topic"
    mosquitto_sub \
        -h $BROKER_HOST \
        -p $BROKER_PORT \
        -u $BROKER_LOGIN \
        -P $BROKER_PASWD \
        -v -d \
        -t $topic
}

usage() {
    echo "Usage: $0 [-t <topic>]" 1>&2
    exit 1
}

while getopts ":t:" option; do
    case "${option}" in
    t)
        t=${OPTARG}
        ;;
    *)
        usage
        ;;
    esac
done
shift $((OPTIND - 1))

if [ -z "${t}" ]; then
    usage
fi

sub ${t}
