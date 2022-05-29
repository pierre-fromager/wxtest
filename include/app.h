
#ifndef APP_MAIN_H
#define APP_MAIN_H

#include <mymqtt.h>
#include <filelogger.h>
#include <mqttbroker.h>

#define APP_NAME "WxTest"
#define APP_LOG_FILENAME "log.txt"

/**
 * @brief App manager
 *
 */
class App : public wxApp
{
public:
    virtual ~App();
    virtual bool OnInit();
    FileLogger *GetLogger();
    myMqtt *GetMqtt();
    MqttBroker *GetBroker();

private:
    FileLogger *m_logger;
    myMqtt *m_mqtt;
    MqttBroker *m_mqtt_broker;
};

wxDECLARE_APP(App);

#endif