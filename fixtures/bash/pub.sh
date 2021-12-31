#!/bin/bash

. config.sh

pub() {
    local topic=$1
    local msg=$2
    mosquitto_pub \
        -h $BROKER_HOST \
        -p $BROKER_PORT \
        -u $BROKER_LOGIN \
        -P $BROKER_PASWD \
        -t $topic \
        -m $msg
}

usage() {
    echo "Usage: $0 [-t <topic>] [-m <msg>]" 1>&2
    exit 1
}

while getopts ":t:m:" option; do
    case "${option}" in
    t)
        t=${OPTARG}
        ;;
    m)
        m=${OPTARG}
        ;;
    *)
        usage
        ;;
    esac
done
shift $((OPTIND - 1))

if [ -z "${t}" ] || [ -z "${m}" ]; then
    usage
fi

pub "${t}" "${m}"
