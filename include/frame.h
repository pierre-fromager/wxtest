
#ifndef APP_FRAME_H
#define APP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/splitter.h>
#include <wx/datetime.h>
#include <wx/intl.h>
#include <wx/listctrl.h>
#include "ranklist.h"

#define APP_FRAME_TITLE "WxQuickStarter"
#define APP_FRAME_STATUS_WELCOME "Welcome !"
#define APP_FRAME_STATUS_OVERHELP "Status bar help string for Hello item"
#define APP_FRAME_MENUBAR_FILE "&File"
#define APP_FRAME_MENUBAR_HELP "&Help"
#define APP_FRAME_ABOUT_MSGBOX_TITLE "About"
#define APP_FRAME_ABOUT_MSGBOX_CONTENT "WQS - Wx Quick Starter\nv0.1"
#define APP_FRAME_HELLO_LOGMSG "Hello my friend!"
#define APP_FRAME_TIMER_DELTA 1000

class AppFrame : public wxFrame
{
public:
    AppFrame(wxApp *app);

private:
    // ctrl ids
    enum class IDs : wxWindowID
    {
        MainWindow = 1000,
        ID_RESET = 1500,
        ID_LIST = 1100,
        ID_BUTTON = 1600,
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
    // button
    wxButton *button = nullptr;
    // menus
    wxMenu *menuFile = nullptr;
    wxMenu *menuHelp = nullptr;
    wxMenuBar *menuBar = nullptr;
    // timer
    wxTimer *timer = nullptr;
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
    void initMenus();
    void initStatusBar();
    void initPanels();
    void initMenuFile();
    void initMenuHelp();
    void initButton();
    void initSizers();
    void initRadiosStatus();
    void initListview();
    void bindMenuEvents();
    void initTimer();
    void bindTimer();
    void OnReset(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnPress(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &evt);
    void OnItemSelect(wxListEvent &event);
    //void OnColSelect(wxListEvent &event);
    void OnStatusChange(wxCommandEvent &event);
};

#endif