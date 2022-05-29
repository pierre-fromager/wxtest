
#ifndef MQTT_BROKER_H
#define MQTT_BROKER_H

#define MQTT_BROKER_MID "pierre"
#define MQTT_BROKER_HOST "192.168.1.49"
#define MQTT_BROKER_PORT 1883
#define MQTT_BROKER_LOGIN "pierre"
#define MQTT_BROKER_PASSWD "pierre"
#define MQTT_BROKER_KEEPALIVE 60
#define MQTT_BROKER_QOS 0
#define MQTT_BROKER_RETAIN false

#include <hostchecker.h>
#include <string>

/**
 * @brief Mqtt broker config
 *
 */
typedef struct mqtt_broker_config_s
{
    std::string host;
    int port, keepalive, qos;
    std::string login;
    std::string password;
    bool retain;
} mqtt_broker_config_t;

/**
 * @brief Mqtt broker manager
 *
 */
class MqttBroker
{
public:
    explicit MqttBroker(void);
    virtual ~MqttBroker(void);
    mqtt_broker_config_t getConfig(void);
    void setConfig(mqtt_broker_config_t config);
    bool alive();

protected:
    mqtt_broker_config_t m_config;
    Hostchecker *m_hostchecker;
};

#endif