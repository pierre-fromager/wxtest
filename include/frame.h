
#ifndef APP_FRAME_H
#define APP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <mqtttopics.h>
#include <frame_icon_xpm.h>
#include <wx/splitter.h>
#include <wx/datetime.h>
#include <wx/intl.h>
#include <ranklistctrl.h>
#include <timestampctrl.h>
#include <observer.h>
#include <credentialdialog.h>

#define APP_LOG_MSG_FRAME_START "Frame start"
#define APP_LOG_MSG_STOP L"App stop"
#define APP_FRAME_TITLE "WxQuickStarter"
#define APP_FRAME_STATUS_WELCOME "Welcome !"
#define APP_FRAME_STATUS_HINT_RESET "Reset all items from list"
#define APP_FRAME_MENUBAR_FILE "&File"
#define APP_FRAME_MENUBAR_HELP "&Help"
#define APP_FRAME_MENUBAR_CONFIG "&Config"
#define APP_FRAME_MENUBAR_CONFIG_MQTT "Mqtt credential config"
#define APP_FRAME_ABOUT_MSGBOX_TITLE "About"
#define APP_FRAME_ABOUT_MSGBOX_CONTENT "WQS - Wx Quick Starter\nv0.1"
#define APP_FRAME_HELLO_LOGMSG "Hello my friend!"
#define APP_FRAME_TIMER_DELTA 1000

/**
 * @brief App frame manager
 *
 */
class AppFrame : public wxFrame
{
public:
    explicit AppFrame(void);
    virtual ~AppFrame(void);
    /**
     * @brief return mqqt client instance
     *
     */
    myMqtt *GetMqtt(void);
    /**
     * @brief return logger instance
     *
     */
    FileLogger *GetLogger(void);

private:
    static const wxSize _FRAME_SIZE;
    enum class IDs : wxWindowID
    {
        MainWindow = 1000,
        ID_RESET = 1500,
        ID_CONF_MQTT = 1550,
        ID_LIST = 1100,
        ID_BUTTON_ADD = 1200,
        ID_BUTTON_FOO = 1201,
        ID_TXT_TS = 1601,
        ID_RAD_BAD = 2000,
        ID_RAD_MEDIUM = 2001,
        ID_RAD_GOOD = 2002,
        ID_RANK_LIST = 3000,
        ID_CRED_DLG = 4000,
        Timer
    };
    wxBoxSizer *vboxLeft = nullptr;
    wxBoxSizer *vboxBottom = nullptr;
    wxBoxSizer *hboxRight = nullptr;
    wxButton *buttonAdd = nullptr;
    wxMenu *menuFile = nullptr;
    wxMenu *menuHelp = nullptr;
    wxMenu *menuConfig = nullptr;
    wxMenuBar *menuBar = nullptr;
    TimestampCtrl *timestampCtrl = nullptr;
    wxString timestamp = "        ";
    wxRadioButton *m_radioBtn1 = nullptr;
    wxRadioButton *m_radioBtn2 = nullptr;
    wxRadioButton *m_radioBtn3 = nullptr;
    wxPanel *leftPanel = nullptr;
    wxPanel *rightPanel = nullptr;
    wxPanel *bottomPanel = nullptr;
    RankListCtrl *rankListCtrl = nullptr;
    int statusId = 1;
    CredentialDialog *m_credential_dlg = nullptr;
    Observer *obsMqttInfo = nullptr;
    AppFrame *initMenus(void);
    AppFrame *initMenuFile(void);
    AppFrame *initMenuHelp(void);
    AppFrame *initMenuConfig(void);
    AppFrame *initStatusBar(void);
    AppFrame *initPanels(void);
    AppFrame *initButtonAdd(void);
    AppFrame *initSizers(void);
    AppFrame *initRadiosStatus(void);
    AppFrame *initListview(void);
    AppFrame *initTimer(void);
    AppFrame *initCredentialDialog(void);
    void bindMenuEvents(void);
    void bindTimer(void);
    void bindMqttEvents(void);
    void OnReset(wxCommandEvent &event);
    void OnConfigMqtt(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnButtonAdd(wxCommandEvent &event);
    void OnCredentialButtonOk(wxCommandEvent &event);
    void OnCredentialButtonCancel(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &evt);
    void OnItemSelect(wxListEvent &event);
    void OnStatusChange(wxCommandEvent &event);
    void OnMqttEvent(MyMqttEvent &ev);
};

#endif