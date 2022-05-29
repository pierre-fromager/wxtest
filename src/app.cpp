#include <mqttbroker.h>
#include <mqtttopics.h>
#include <frame.h>
#include <app.h>

wxIMPLEMENT_APP(App);

AppFrame *m_frame;

bool App::OnInit()
{
    m_logger = new FileLogger(APP_LOG_FILENAME);
    m_logger->SetLevel(static_cast<logger_level_t>(FileLogger::Levels::Debug));
    SetAppName(APP_NAME);
    SetAppDisplayName(APP_NAME);
    std::vector<std::string> subscr_topics = {MQTT_TOPIC_DEFAULT_SUB};
    m_mqtt_broker = new MqttBroker();
    m_mqtt = new myMqtt(MQTT_BROKER_MID, MQTT_TOPIC_DEFAULT_PUB, subscr_topics, m_mqtt_broker);
    m_frame = new AppFrame();
    SetTopWindow(m_frame);
    m_mqtt->setEventHanlder(m_frame->GetEventHandler());
    m_mqtt->subscribe();
    m_frame->Show(true);
    return true;
}

App::~App()
{
    //wxDELETE(m_frame);
    wxDELETE(m_mqtt_broker);
    wxDELETE(m_mqtt);
    wxDELETE(m_logger);
}

FileLogger *App::GetLogger()
{
    return m_logger;
}

myMqtt *App::GetMqtt()
{
    return m_mqtt;
}
