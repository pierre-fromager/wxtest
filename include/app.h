#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "logger.h"

#define APP_NAME "WxTest"
#define APP_LOG_FILENAME "log.txt"
#define APP_LOG_MSG_START L"App start"

class App : public wxApp
{
    
public:
    virtual ~App();
    virtual bool OnInit();
    //wxLog *GetLogger();
    //void logDebug(const char *format, ...);
    Logger *GetLogger();

private:
    FILE *m_pLogFile = nullptr;
    char *m_log_line;
    Logger *m_logger;
    //wxLog *m_logger = nullptr;
};


wxDECLARE_APP(App);

#endif