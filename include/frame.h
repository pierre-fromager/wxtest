
#ifndef APP_FRAME_H
#define APP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "fooevent.h"
#include "frame_icon_xpm.h"
#include <wx/splitter.h>
#include <wx/datetime.h>
#include <wx/intl.h>
#include "ranklistctrl.h"
#include "timestampctrl.h"
#include "app.h"

#define APP_LOG_MSG_FRAME_START "Frame start"
#define APP_LOG_MSG_STOP L"App stop"
#define APP_FRAME_TITLE "WxQuickStarter"
#define APP_FRAME_STATUS_WELCOME "Welcome !"
#define APP_FRAME_STATUS_HINT_RESET "Reset all items from list"
#define APP_FRAME_MENUBAR_FILE "&File"
#define APP_FRAME_MENUBAR_HELP "&Help"
#define APP_FRAME_ABOUT_MSGBOX_TITLE "About"
#define APP_FRAME_ABOUT_MSGBOX_CONTENT "WQS - Wx Quick Starter\nv0.1"
#define APP_FRAME_HELLO_LOGMSG "Hello my friend!"
#define APP_FRAME_TIMER_DELTA 1000

class AppFrame : public wxFrame
{
public:
    AppFrame();

private:
    // ctrl ids
    enum class IDs : wxWindowID
    {
        MainWindow = 1000,
        ID_RESET = 1500,
        ID_LIST = 1100,
        ID_BUTTON_ADD = 1200,
        ID_BUTTON_FOO = 1201,
        ID_TXT_TS = 1601,
        ID_RAD_BAD = 2000,
        ID_RAD_MEDIUM = 2001,
        ID_RAD_GOOD = 2002,
        ID_RANK_LIST = 3000,
        Timer
    };
    // sizers
    wxBoxSizer *vboxLeft = nullptr;
    wxBoxSizer *vboxBottom = nullptr;
    wxBoxSizer *hboxRight = nullptr;
    // buttons
    wxButton *buttonAdd = nullptr;
    wxButton *fooButton  = nullptr;
    // menus
    wxMenu *menuFile = nullptr;
    wxMenu *menuHelp = nullptr;
    wxMenuBar *menuBar = nullptr;
    // timer
    //wxTimer *timer = nullptr;
    TimestampCtrl *timestampCtrl = nullptr;
    wxString timestamp = "        ";
    // radios
    wxRadioButton *m_radioBtn1 = nullptr;
    wxRadioButton *m_radioBtn2 = nullptr;
    wxRadioButton *m_radioBtn3 = nullptr;
    // panels
    wxPanel *leftPanel = nullptr;
    wxPanel *rightPanel = nullptr;
    wxPanel *bottomPanel = nullptr;
    // ranklistctrl
    RankListCtrl *rankListCtrl = nullptr;
    // internals
    int statusId = 1;
    // voids
    FileLogger *GetLogger();
    void initMenus();
    void initMenuFile();
    void initMenuHelp();
    void initStatusBar();
    void initPanels();
    void initButtonAdd();
    void initButtonGenFoo();
    void initSizers();
    void initRadiosStatus();
    void initListview();
    void bindMenuEvents();
    void initTimer();
    void bindTimer();
    void bindFooEvents();
    void OnReset(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnButtonAdd(wxCommandEvent &event);
    void OnButtonFoo(wxCommandEvent &event);
    void OnFooEvent(MyFooEvent &ev);
    void OnTimer(wxTimerEvent &evt);
    void OnItemSelect(wxListEvent &event);
    void OnStatusChange(wxCommandEvent &event);
};

#endif