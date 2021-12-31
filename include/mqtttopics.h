
#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

#define MQTT_FRAG_TOPIC_ROOT "wxtest/"
#define MQTT_FRAG_TOPIC_APP "app"
#define MQTT_FRAG_TOPIC_ROOT_APP MQTT_FRAG_TOPIC_ROOT MQTT_FRAG_TOPIC_APP
#define MQTT_FRAG_TOPIC_STATE "/state/"
#define MQTT_FRAG_TOPIC_CONTROL "/control/"
#define MQTT_FRAG_TOPIC_STATUSID "statusid"
#define MQTT_FRAG_TOPIC_RESET "reset"

#define MQTT_TOPIC_DEFAULT_SUB \
    MQTT_FRAG_TOPIC_ROOT_APP   \
    MQTT_FRAG_TOPIC_CONTROL "#"

#define MQTT_TOPIC_DEFAULT_PUB \
    MQTT_FRAG_TOPIC_ROOT_APP

#define MQTT_TOPIC_PUBLISH_STATUS \
    MQTT_FRAG_TOPIC_ROOT_APP      \
    MQTT_FRAG_TOPIC_STATE MQTT_FRAG_TOPIC_STATUSID

#define MQTT_TOPIC_PUBLISH_RESET \
    MQTT_FRAG_TOPIC_ROOT_APP     \
    MQTT_FRAG_TOPIC_STATE MQTT_FRAG_TOPIC_RESET

#define MQTT_TOPIC_PUBLISH_ITEM \
    MQTT_FRAG_TOPIC_ROOT_APP    \
    MQTT_FRAG_TOPIC_STATE "item"

#define MQTT_TOPIC_CONTROL_STATUS \
    MQTT_FRAG_TOPIC_ROOT_APP      \
    MQTT_FRAG_TOPIC_CONTROL       \
    "state/" MQTT_FRAG_TOPIC_STATUSID

#define MQTT_TOPIC_CONTROL_RESET \
    MQTT_FRAG_TOPIC_ROOT_APP     \
    MQTT_FRAG_TOPIC_CONTROL      \
    "state/" MQTT_FRAG_TOPIC_RESET

#define MQTT_TOPIC_CONTROL_ADD \
    MQTT_FRAG_TOPIC_ROOT_APP   \
    MQTT_FRAG_TOPIC_CONTROL    \
    "state/add"

#endif