
#ifndef APP_FRAME_H
#define APP_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/datetime.h>
#include <wx/intl.h>
#include <wx/listctrl.h>

#include "sort.h"

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
        ID_Hello = 1,
        ID_List = 100,
        ID_Button = wxID_HIGHEST + 1
    };
    wxPanel *panel = nullptr;
    wxGridSizer *grid = nullptr;
    wxBoxSizer *vbox = nullptr;
    wxButton *button = nullptr;
    wxListCtrl *listview = nullptr;
    wxMenu *menuFile = nullptr;
    wxMenu *menuHelp = nullptr;
    wxMenuBar *menuBar = nullptr;
    wxTimer *timer = nullptr;
    wxString timestamp = "        ";
    int col0order = 0;
    int itemIndex = 0;
    void initMenus();
    void initStatusBar();
    void initPanel();
    void initMenuFile();
    void initMenuHelp();
    void initButton();
    void initGrid();
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
    void OnColSelect(wxListEvent &event);
};

#endif