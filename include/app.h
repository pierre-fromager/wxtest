#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "mymqtt.h"
#include "filelogger.h"

#define APP_NAME "WxTest"
#define APP_LOG_FILENAME "log.txt"
#define APP_MQTT_DEFAULT_MID "pierre"
#define APP_MQTT_DEFAULT_HOST "192.168.3.60"
#define APP_MQTT_DEFAULT_PORT 1883
#define APP_MQTT_DEFAULT_LOGIN "pierre"
#define APP_MQTT_DEFAULT_PASSWD "pierre"
#define APP_MQTT_DEFAULT_TOPICS_SUB "wxwidget/app/#"
#define APP_MQTT_DEFAULT_TOPICS_PUB "wxwidget/app"

class App : public wxApp
{
public:
    virtual ~App();
    virtual bool OnInit();
    FileLogger *GetLogger();
    myMqtt *GetMqtt();

private:
    FileLogger *m_logger;
    myMqtt *m_mqtt;
};

wxDECLARE_APP(App);

#endif