#include "frame.h"

AppFrame::AppFrame(wxApp *app)
    : wxFrame(
          nullptr,
          static_cast<wxWindowID>(IDs::MainWindow),
          wxString(app->GetAppDisplayName()))
{
    app->SetAppDisplayName(APP_FRAME_TITLE);
    initMenus();
    CreateStatusBar();
    SetStatusText(APP_FRAME_STATUS_WELCOME);
    bindMenuEvents();
    initTimer();
    bindTimer();
    initClock();
    m_timer->Start(APP_FRAME_TIMER_DELTA, wxTIMER_CONTINUOUS);
}

void AppFrame::initClock()
{
    m_clockDisplay = new wxStaticText(
        this,
        wxID_ANY,
        "Timer",
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
    wxFont font = m_clockDisplay->GetFont();
    font.MakeBold().MakeLarger();
    m_clockDisplay->SetFont(font);
}

void AppFrame::initMenus()
{
    initMenuFile();
    initMenuHelp();
    m_menuBar = new wxMenuBar;
    m_menuBar->Append(m_menuFile, APP_FRAME_MENUBAR_FILE);
    m_menuBar->Append(m_menuHelp, APP_FRAME_MENUBAR_HELP);
    SetMenuBar(m_menuBar);
}

void AppFrame::initMenuFile()
{
    m_menuFile = new wxMenu;
    m_menuFile->Append(
        ID_Hello,
        "&Hello...\tCtrl-H",
        APP_FRAME_STATUS_OVERHELP);
    m_menuFile->AppendSeparator();
    m_menuFile->Append(wxID_EXIT);
}

void AppFrame::initMenuHelp()
{
    m_menuHelp = new wxMenu;
    m_menuHelp->Append(wxID_ABOUT);
}

void AppFrame::bindMenuEvents()
{
    Bind(wxEVT_MENU, &AppFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &AppFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
}

void AppFrame::initTimer()
{
    m_timer = new wxTimer(this, static_cast<int>(IDs::Timer));
}

void AppFrame::bindTimer()
{
    Bind(wxEVT_TIMER, &AppFrame::OnTimer, this, m_timer->GetId());
}

void AppFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(
        APP_FRAME_ABOUT_MSGBOX_CONTENT,
        APP_FRAME_ABOUT_MSGBOX_TITLE,
        wxOK | wxICON_INFORMATION);
}

void AppFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage(APP_FRAME_HELLO_LOGMSG);
}

void AppFrame::OnTimer(wxTimerEvent &evt)
{
    wxUnusedVar(evt);
    m_clockDisplay->SetLabel(wxDateTime::Now().FormatTime());
}