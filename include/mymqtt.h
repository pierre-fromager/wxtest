
#ifndef APP_MYMQTT_H
#define APP_MYMQTT_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <mosquittopp.h>

using namespace std;

#define MYMQTT_PINGRESP "PINGRESP"
#define MYMQTT_PINGREQ "PINGREQ"

/**
 * @brief myMqtt client
 * @url https://github.com/mec-kon/simple-mqtt-client
 * 
 */
class myMqtt : public mosqpp::mosquittopp
{

public:
    myMqtt(
        string id,
        string publish_topic,
        vector<string> subscribed_topics,
        string host,
        int port);
    myMqtt(
        string id,
        string publish_topic,
        vector<string> subscribed_topics,
        string host,
        int port,
        string username,
        string password);
    ~myMqtt();
    bool publish(string message);
    bool subscribe();
    bool unsubscribe(string topic);

private:
    string m_id;
    string m_publish_topic;
    vector<string> m_subscribed_topics;
    string m_host;
    int m_port;
    string m_username;
    string m_password;
    const int m_keepalive = 60;
    const int m_qos = 0;
    const bool m_retain = false;
    void on_connect(int rc);
    void on_disconnect(int rc);
    void on_publish(int mid);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    void on_unsubscribe(int mid);
    void on_log(int level, const char *str);
    void on_error();
};

#endif