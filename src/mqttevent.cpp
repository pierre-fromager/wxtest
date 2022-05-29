
#include "mqttevent.h"

wxDEFINE_EVENT(myEVT_MQTT, MyMqttEvent);

MyMqttEvent::MyMqttEvent(
    wxEventType evType = myEVT_MQTT,
    int id = 0) : wxCommandEvent(evType, id) {}

MyMqttEvent::MyMqttEvent(const MyMqttEvent &ev) : wxCommandEvent(ev)
{
    this->SetTopic(ev.GetTopic());
    this->SetPayload(ev.GetPayload());
}

wxEvent *MyMqttEvent::Clone(void) const
{
    return new MyMqttEvent(*this);
}

void MyMqttEvent::SetTopic(const std::string &topic)
{
    m_topic = topic;
}

void MyMqttEvent::SetPayload(const std::string &payload)
{
    m_payload = payload;
}

std::string MyMqttEvent::GetTopic(void) const
{
    return m_topic;
}

std::string MyMqttEvent::GetPayload(void) const
{
    return m_payload;
}