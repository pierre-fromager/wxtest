

#include "frame.h"
#include "app.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_logger = new FileLogger(APP_LOG_FILENAME);
    m_logger->SetLevel(static_cast<logger_level_t>(FileLogger::Levels::Debug));
    const std::string pseudo = "pierre";
    const std::string lpasswd = "pierre";
    std::vector<std::string> topics = {"wxwidget/app/#"};
    m_mqtt = new myMqtt(
        pseudo,
        "wxwidget/app",
        topics,
        "192.168.3.60",
        1883,
        lpasswd,
        lpasswd);
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
