
#include "mymqtt.h"

myMqtt::myMqtt(
    string id,
    string publish_topic,
    vector<string> subscribed_topics,
    string host,
    int port) : mosquittopp(id.c_str()),
                m_id(id),
                m_publish_topic(publish_topic),
                m_subscribed_topics(subscribed_topics),
                m_host(host),
                m_port(port)
{
    mosqpp::lib_init();
    mosqpp::mosquittopp::connect_async(m_host.c_str(), m_port, m_keepalive);
    mosqpp::mosquittopp::loop_start();
}

myMqtt::myMqtt(
    string id,
    string publish_topic,
    vector<string> subscribed_topics,
    string host,
    int port,
    string username,
    string password) : mosquittopp(id.c_str()),
                       m_id(id),
                       m_publish_topic(publish_topic),
                       m_subscribed_topics(subscribed_topics),
                       m_host(host),
                       m_port(port),
                       m_username(username),
                       m_password(password)

{
    mosqpp::lib_init();
    mosquittopp::username_pw_set(m_username.c_str(), m_password.c_str());
    mosqpp::mosquittopp::connect_async(m_host.c_str(), m_port, m_keepalive);
    mosqpp::mosquittopp::loop_start();
}

myMqtt::~myMqtt()
{
    mosqpp::mosquittopp::disconnect();
    mosqpp::mosquittopp::loop_stop();
    mosqpp::lib_cleanup();
}

void myMqtt::setPublishTopic(string topic)
{
    m_publish_topic = topic;
}

bool myMqtt::publish(string msg)
{
    const int &answer = mosqpp::mosquittopp::publish(
        nullptr,
        m_publish_topic.c_str(),
        msg.length(),
        msg.c_str(),
        m_qos,
        m_retain);
    return (answer == MOSQ_ERR_SUCCESS);
}

bool myMqtt::subscribe()
{
    bool success = true;
    const unsigned int &numberOfTopics = m_subscribed_topics.size();
    unsigned int i;
    for (i = 0; i < numberOfTopics; i++)
    {
        int answer = mosqpp::mosquittopp::subscribe(nullptr, m_subscribed_topics[i].c_str());
        if (answer != MOSQ_ERR_SUCCESS)
        {
            success = false;
        }
    }
    return success;
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
    cout << "Subscribed success." << endl;
}

void myMqtt::on_message(const struct mosquitto_message *message)
{
    string payload = string(static_cast<char *>(message->payload));
    string topic = string(message->topic);
    cout << "payload: " << payload << endl;
    cout << "topic: " << topic << endl;
}

void myMqtt::on_disconnect(int rc)
{
    cout << "disconnected(" << rc << ")" << endl;
}

void myMqtt::on_connect(int rc)
{
    const string &status = (rc == 0) ? "success" : "fail";
    cout << "connect " << status << " (" << rc << ")" << endl;
}

void myMqtt::on_publish(int mid)
{
    cout << "Message (" << mid << ") succeed to be published " << endl;
}

void myMqtt::on_unsubscribe(int mid)
{
    cout << "Unsubscribed success." << endl;
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
    cout << "Error happened" << endl;
}
