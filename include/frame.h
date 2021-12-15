
#ifndef APP_FRAME_H
#define APP_FRAME_H

#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/intl.h>

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
    enum class IDs : wxWindowID
    {
        MainWindow = 1000,
        Timer
    };
    enum
    {
        ID_Hello = 1
    };
    wxMenu *m_menuFile = nullptr;
    wxMenu *m_menuHelp = nullptr;
    wxMenuBar *m_menuBar = nullptr;
    wxTimer *m_timer = nullptr;
    wxStaticText *m_clockDisplay = nullptr;
    void initMenus();
    void initMenuFile();
    void initMenuHelp();
    void initClock();
    void bindMenuEvents();
    void initTimer();
    void bindTimer();
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnTimer(wxTimerEvent &evt);
};

#endif