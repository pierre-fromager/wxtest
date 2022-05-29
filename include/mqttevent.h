#ifndef APP_MQTTEVENT_H
#define APP_MQTTEVENT_H

#include <string>
#include <vector>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/**
 * @brief Mqtt event manager
 *
 */
class MyMqttEvent : public wxCommandEvent
{

public:
    MyMqttEvent(wxEventType evType, int id);
    MyMqttEvent(const MyMqttEvent &ev);
    virtual wxEvent *Clone(void) const override;
    void SetTopic(const std::string &topic);
    void SetPayload(const std::string &payload);
    std::string GetTopic(void) const;
    std::string GetPayload(void) const;

private:
    std::string m_topic;
    std::string m_payload;
};

wxDECLARE_EVENT(myEVT_MQTT, MyMqttEvent);

#endif