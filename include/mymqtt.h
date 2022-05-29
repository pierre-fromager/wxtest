
#ifndef APP_MYMQTT_H
#define APP_MYMQTT_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <mosquittopp.h>
#include <mqttevent.h>
#include <mqttbroker.h>
#include <subject.h>

using namespace std;

#define MYMQTT_PINGRESP "PINGRESP"
#define MYMQTT_PINGREQ "PINGREQ"

/**
 * @brief Mqtt client
 *
 */
class myMqtt : public mosqpp::mosquittopp
{

public:
    myMqtt(
        string id,
        string publish_topic,
        vector<string> subscribed_topics,
        MqttBroker *broker);
    ~myMqtt();
    mqtt_broker_config_t getConfig();
    void setConfig(mqtt_broker_config_t config);
    bool connect(void);
    bool isConnected(void);
    bool disconnect(void);
    myMqtt *setUsername(string username);
    myMqtt *setPassword(string passwd);
    myMqtt *setHost(string host);
    myMqtt *setPort(int port);
    void setPublishTopic(string topic);
    bool publish(string message);
    bool subscribe(void);
    bool unsubscribe(string topic);
    Subject *subjectInfo();
    myMqtt *setEventHanlder(wxEvtHandler *evthandler);

private:
    wxEvtHandler *m_evthandler;
    string m_id;
    string m_publish_topic;
    vector<string> m_subscribed_topics;
    MqttBroker *m_broker;
    bool m_is_connected;
    Subject *m_info_subject;
    void on_connect(int rc);
    void on_disconnect(int rc);
    void on_publish(int mid);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    void on_unsubscribe(int mid);
    void on_log(int level, const char *str);
    void on_error(void);
};

#endif