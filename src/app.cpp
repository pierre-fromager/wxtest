
#include "mqttbroker.h"
#include "mqtttopics.h"
#include "frame.h"
#include "app.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_logger = new FileLogger(APP_LOG_FILENAME);
    m_logger->SetLevel(static_cast<logger_level_t>(FileLogger::Levels::Debug));
    SetAppName(APP_NAME);
    SetAppDisplayName(APP_NAME);
    AppFrame *appFrame = new AppFrame();
    SetTopWindow(appFrame);
    appFrame->Show(true);
    std::vector<std::string> subscr_topics = {MQTT_TOPIC_DEFAULT_SUB};
    m_mqtt = new myMqtt(
        MQTT_BROKER_MID,
        MQTT_TOPIC_DEFAULT_PUB,
        subscr_topics,
        MQTT_BROKER_HOST,
        MQTT_BROKER_PORT,
        MQTT_BROKER_LOGIN,
        MQTT_BROKER_PASSWD);
    m_mqtt->setEventHanlder(appFrame->GetEventHandler());
    m_mqtt->subscribe();
    return true;
}

App::~App()
{
    delete m_logger;
    delete m_mqtt;
}

FileLogger *App::GetLogger()
{
    return m_logger;
}

myMqtt *App::GetMqtt()
{
    return m_mqtt;
}
