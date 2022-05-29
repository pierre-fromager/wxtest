
#include "mqttbroker.h"

MqttBroker::MqttBroker(void)
{
    m_config.host = MQTT_BROKER_HOST;
    m_config.port = MQTT_BROKER_PORT;
    m_config.keepalive = MQTT_BROKER_KEEPALIVE;
    m_config.qos = MQTT_BROKER_QOS;
    m_config.retain = MQTT_BROKER_RETAIN;
    m_config.login = MQTT_BROKER_LOGIN;
    m_config.password = MQTT_BROKER_PASSWD;
    m_hostchecker = new Hostchecker(m_config.host, m_config.port);
}

MqttBroker::~MqttBroker(void)
{
    //wxDELETE(m_hostchecker);
}

bool MqttBroker::alive()
{
    return m_hostchecker->alive();
}

mqtt_broker_config_t MqttBroker::getConfig(void)
{
    return m_config;
}

void MqttBroker::setConfig(mqtt_broker_config_t config)
{
    m_config = config;
    m_hostchecker->setHost(m_config.host);
    m_hostchecker->setPort(m_config.port);
}