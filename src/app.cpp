

#include "frame.h"
#include "app.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    m_logger = new Logger(APP_LOG_FILENAME);
    m_logger->SetLevel(static_cast<logger_level_t>(Logger::Levels::Debug));
    SetAppDisplayName(APP_NAME);
    AppFrame *appFrame = new AppFrame();
    SetTopWindow(appFrame);
    appFrame->Show(true);
    return true;
}

App::~App()
{
    delete m_logger;
}

Logger *App::GetLogger()
{
    return m_logger;
}
