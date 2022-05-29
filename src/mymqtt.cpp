
#include "mymqtt.h"

myMqtt::myMqtt(
    string id,
    string publish_topic,
    vector<string> subscribed_topics,
    MqttBroker *broker) : mosquittopp(id.c_str()),
                          m_id(id),
                          m_publish_topic(publish_topic),
                          m_subscribed_topics(subscribed_topics),
                          m_broker(broker)
{
    m_is_connected = false;
    m_info_subject = new Subject;
    m_info_subject->CreateMessage("MyMqtt host : " + m_broker->getConfig().host);
}

myMqtt::~myMqtt()
{
    if (true == isConnected())
    {
        disconnect();
    }
    wxDELETE(m_info_subject);
}

Subject *myMqtt::subjectInfo()
{
    return m_info_subject;
}

bool myMqtt::isConnected(void)
{
    return (true == m_is_connected);
}

mqtt_broker_config_t myMqtt::getConfig()
{
    return m_broker->getConfig();
}

void myMqtt::setConfig(mqtt_broker_config_t config)
{
    m_broker->setConfig(config);
}

bool myMqtt::connect()
{
    int rc = 0;
    m_info_subject->CreateMessage("MQTT trying to connect");
    if (true == m_broker->alive())
    {
        m_info_subject->CreateMessage("MQTT host is alive");
        const mqtt_broker_config_t config = getConfig();
        rc = mosqpp::lib_init();
        m_info_subject->CreateMessage((0 == rc) ? "MQTT init succes" : "MQTT init failed");
        if (config.login.length() > 0 && config.password.length() > 0)
        {
            m_info_subject->CreateMessage("MQTT applying credentials");
            rc += mosquittopp::username_pw_set(config.login.c_str(), config.password.c_str());
            m_info_subject->CreateMessage((0 == rc) ? "MQTT credentials succes" : "MQTT credentials failed");
        }
        rc += mosqpp::mosquittopp::connect_async(config.host.c_str(), config.port, config.keepalive);
        m_info_subject->CreateMessage((0 == rc) ? "MQTT connect succes" : "MQTT connect failed");
        rc += mosqpp::mosquittopp::loop_start();
        m_info_subject->CreateMessage((0 == rc) ? "MQTT loop succes" : "MQTT loop failed");
    }
    else
    {
        m_info_subject->CreateMessage("MQTT host is dead");
        rc += 1;
    }
    m_is_connected = (rc == 0);
    return m_is_connected;
}

bool myMqtt::disconnect()
{
    int rc = 0;
    if (true == isConnected())
    {
        rc = mosqpp::mosquittopp::disconnect();
        rc += mosqpp::mosquittopp::loop_stop();
        rc += mosqpp::lib_cleanup();
        m_info_subject->CreateMessage("MQTT disconnect error");
    }
    return (rc == 0);
}

myMqtt *myMqtt::setUsername(string username)
{
    mqtt_broker_config_t conf = getConfig();
    conf.login = username;
    m_broker->setConfig(conf);
    return this;
}

myMqtt *myMqtt::setPassword(string passwd)
{
    mqtt_broker_config_t conf = getConfig();
    conf.password = passwd;
    m_broker->setConfig(conf);
    return this;
}

myMqtt *myMqtt::setHost(string host)
{
    mqtt_broker_config_t conf = getConfig();
    conf.host = host;
    m_broker->setConfig(conf);
    return this;
}

myMqtt *myMqtt::setPort(int port)
{
    mqtt_broker_config_t conf = getConfig();
    conf.port = port;
    m_broker->setConfig(conf);
    return this;
}

void myMqtt::setPublishTopic(string topic)
{
    m_publish_topic = topic;
}

bool myMqtt::publish(string msg)
{
    const mqtt_broker_config_t conf = getConfig();
    const int &answer = mosqpp::mosquittopp::publish(
        nullptr,
        m_publish_topic.c_str(),
        msg.length(),
        msg.c_str(),
        conf.qos,
        conf.retain);
    return (answer == MOSQ_ERR_SUCCESS);
}

bool myMqtt::subscribe()
{
    bool success = true;
    const unsigned int &numberOfTopics = m_subscribed_topics.size();
    unsigned int i;
    int rc = 0;
    for (i = 0; i < numberOfTopics; i++)
    {
        rc += mosqpp::mosquittopp::subscribe(nullptr, m_subscribed_topics[i].c_str());
    }
    return (0 == rc);
}

bool myMqtt::unsubscribe(string topic)
{
    bool success = true;
    const unsigned int &numberOfTopics = m_subscribed_topics.size();
    unsigned int i;
    for (i = 0; i < numberOfTopics; i++)
    {
        if (topic.compare(m_subscribed_topics[i].c_str()) == 0)
        {
            int answer = mosqpp::mosquittopp::unsubscribe(nullptr, topic.c_str());
            if (answer != MOSQ_ERR_SUCCESS)
            {
                success = false;
            }
        }
    }
    return success;
}

void myMqtt::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    m_info_subject->CreateMessage("Subscribed success.");
}

myMqtt *myMqtt::setEventHanlder(wxEvtHandler *evthandler)
{
    m_evthandler = evthandler;
    return this;
}

void myMqtt::on_message(const struct mosquitto_message *message)
{
    string payload = string(static_cast<char *>(message->payload));
    string topic = string(message->topic);
    // cout << "payload: " << payload << endl;
    // cout << "topic: " << topic << endl;
    MyMqttEvent *m_mqttevt = new MyMqttEvent(myEVT_MQTT, 0);
    m_mqttevt->SetTopic(topic);
    m_mqttevt->SetPayload(payload);
    wxQueueEvent(m_evthandler, m_mqttevt);
}

void myMqtt::on_disconnect(int rc)
{
    char cmsh[256];
    sprintf(cmsh, "Mqtt disconnected(%d)", rc);
    const std::string msg(cmsh);
    m_info_subject->CreateMessage(msg);
}

void myMqtt::on_connect(int rc)
{
    const string &status = (rc == 0) ? "success" : "fail";
    m_info_subject->CreateMessage("MQTT connect " + status);
}

void myMqtt::on_publish(int mid)
{
    m_info_subject->CreateMessage("MQTT msg published");
}

void myMqtt::on_unsubscribe(int mid)
{
    m_info_subject->CreateMessage("Unsubscribed success.");
}

void myMqtt::on_log(int level, const char *str)
{
    const bool isPingReq = strcmp(str, MYMQTT_PINGREQ);
    const bool isPingRes = strcmp(str, MYMQTT_PINGRESP);
    const bool isPing = (isPingReq || isPingRes);
    if (!isPing)
        cout << "log(" << level << "):" << str << endl;
}

void myMqtt::on_error()
{
    m_info_subject->CreateMessage("Error happened");
}
