

#include "frame.h"
#include "app.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_logger = new FileLogger(APP_LOG_FILENAME);
    m_logger->SetLevel(static_cast<logger_level_t>(FileLogger::Levels::Debug));
    std::vector<std::string> topics = {APP_MQTT_DEFAULT_TOPICS_SUB};
    m_mqtt = new myMqtt(
        APP_MQTT_DEFAULT_MID,
        APP_MQTT_DEFAULT_TOPICS_PUB,
        topics,
        APP_MQTT_DEFAULT_HOST,
        APP_MQTT_DEFAULT_PORT,
        APP_MQTT_DEFAULT_LOGIN,
        APP_MQTT_DEFAULT_PASSWD);
    m_mqtt->subscribe();
    SetAppName(APP_NAME);
    SetAppDisplayName(APP_NAME);
    AppFrame *appFrame = new AppFrame();
    SetTopWindow(appFrame);
    appFrame->Show(true);
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
