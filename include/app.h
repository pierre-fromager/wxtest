#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "filelogger.h"

#define APP_NAME "WxTest"
#define APP_LOG_FILENAME "log.txt"

class App : public wxApp
{
public:
    virtual ~App();
    virtual bool OnInit();
    FileLogger *GetLogger();

private:
    FileLogger *m_logger;
};

wxDECLARE_APP(App);

#endif