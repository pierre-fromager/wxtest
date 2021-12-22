
#include "frame.h"

AppFrame::AppFrame()
    : wxFrame(
          nullptr,
          static_cast<wxWindowID>(IDs::MainWindow),
          wxString(wxGetApp().GetAppName()),
          wxDefaultPosition,
          wxSize(640, 480))
{
    SetIcon(asset_frame_icon);
    GetLogger()->Debug(APP_LOG_MSG_FRAME_START);
    initMenus();
    initStatusBar();
    initPanels();
    initRadiosStatus();
    initListview();
    initButtonAdd();
    initButtonGenFoo();
    initTimer();
    initSizers();
    bindMenuEvents();
    bindTimer();
    bindFooEvents();
    timestampCtrl->TimerStart();
}

void AppFrame::initSizers()
{
    const int LeftProportion = wxEXPAND | wxTOP | wxBOTTOM;
    vboxLeft = new wxBoxSizer(wxVERTICAL);
    vboxLeft->Add(timestampCtrl, 0, LeftProportion, 1);
    vboxLeft->Add(m_radioBtn1, 0, LeftProportion, 1);
    vboxLeft->Add(m_radioBtn2, 0, LeftProportion, 1);
    vboxLeft->Add(m_radioBtn3, 0, LeftProportion, 1);
    vboxLeft->Add(buttonAdd, 1, LeftProportion, 3);
    leftPanel->SetSizer(vboxLeft);
    vboxBottom = new wxBoxSizer(wxVERTICAL);
    vboxBottom->Add(rankListCtrl, 1, LeftProportion, 3);
    bottomPanel->SetSizer(vboxBottom);
    hboxRight = new wxBoxSizer(wxHORIZONTAL);
    hboxRight->Add(fooButton, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    rightPanel->SetSizer(hboxRight);
}

void AppFrame::bindFooEvents()
{
    Bind(myEVT_FOO, &AppFrame::OnFooEvent, this, wxID_ANY);
}

void AppFrame::OnFooEvent(MyFooEvent &ev)
{
    GetLogger()->Debug(
        "%s id=%d x=%f y=%f",
        __PRETTY_FUNCTION__,
        ev.GetId(),
        ev.GetPoint().x,
        ev.GetPoint().y);
}

void AppFrame::OnButtonFoo(wxCommandEvent &ev)
{
    wxUnusedVar(ev);
    MyFooEvent *event = new MyFooEvent(myEVT_FOO, statusId);
    wxRealPoint rp(1.01, 2.02);
    event->SetPoint(rp);
    wxQueueEvent(this, event);
}

void AppFrame::initRadiosStatus()
{
    const wxSize &rs = wxSize(20, 20);
    const wxWindowID &ridBad = static_cast<wxWindowID>(IDs::ID_RAD_BAD);
    const wxWindowID &ridMedium = static_cast<wxWindowID>(IDs::ID_RAD_MEDIUM);
    const wxWindowID &ridGood = static_cast<wxWindowID>(IDs::ID_RAD_GOOD);
    const wxPoint &dpos = wxDefaultPosition;
    m_radioBtn1 = new wxRadioButton(leftPanel, ridBad, _("&Bad"), dpos, rs, wxRB_GROUP);
    m_radioBtn1->SetValue(true);
    Bind(wxEVT_RADIOBUTTON, &AppFrame::OnStatusChange, this, ridBad);
    m_radioBtn2 = new wxRadioButton(leftPanel, ridMedium, _("&Medium"), dpos, rs, 0);
    Bind(wxEVT_RADIOBUTTON, &AppFrame::OnStatusChange, this, ridMedium);
    m_radioBtn3 = new wxRadioButton(leftPanel, ridGood, _("&Good"), dpos, rs, 0);
    Bind(wxEVT_RADIOBUTTON, &AppFrame::OnStatusChange, this, ridGood);
}

void AppFrame::initPanels()
{
    wxSplitterWindow *splitter = new wxSplitterWindow(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_3D | wxSP_LIVE_UPDATE);
    wxSplitterWindow *right_splitter = new wxSplitterWindow(
        splitter,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_3D | wxSP_LIVE_UPDATE);
    leftPanel = new wxPanel(splitter);
    rightPanel = new wxPanel(right_splitter);
    bottomPanel = new wxPanel(right_splitter);
#ifdef APP_FRAME_DEBUG
    leftPanel->SetBackgroundColour(wxColor(200, 100, 100));
    rightPanel->SetBackgroundColour(wxColor(100, 200, 100));
    bottomPanel->SetBackgroundColour(wxColor(200, 200, 100));
#endif
    right_splitter->SetMinimumPaneSize(50);
    right_splitter->SplitHorizontally(rightPanel, bottomPanel);
    right_splitter->SetSashGravity(0);
    right_splitter->SetSashPosition(50, true);
    splitter->SetMinimumPaneSize(100);
    splitter->SplitVertically(leftPanel, right_splitter);
    splitter->SetSashPosition(100, true);
}

void AppFrame::initListview()
{
    rankListCtrl = new RankListCtrl(bottomPanel);
    const wxWindowID &rlId = static_cast<wxWindowID>(IDs::ID_RANK_LIST);
    rankListCtrl->SetId(rlId);
    Bind(wxEVT_LIST_ITEM_SELECTED, &AppFrame::OnItemSelect, this, rlId);
}

void AppFrame::OnItemSelect(wxListEvent &event)
{
    const RankItem &r = rankListCtrl->GetRank(event.GetIndex());
    GetLogger()->Debug(
        "OnItemSelect index:%s | timestamp:%s | status:%s",
        (const_cast<char *>((const char *)r.index.mb_str())),
        (const_cast<char *>((const char *)r.timestamp.mb_str())),
        (const_cast<char *>((const char *)r.status.mb_str())));
}

void AppFrame::initButtonAdd()
{
    const wxWindowID &bid = static_cast<wxWindowID>(IDs::ID_BUTTON_ADD);
    buttonAdd = new wxButton(leftPanel, bid, _("&Add"));
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnButtonAdd, this, bid);
}

void AppFrame::initButtonGenFoo()
{
    const wxWindowID &bid = static_cast<wxWindowID>(IDs::ID_BUTTON_FOO);
    fooButton = new wxButton(rightPanel, bid, "GenFooEvent");
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnButtonFoo, this, bid);
}

FileLogger *AppFrame::GetLogger()
{
    return wxGetApp().GetLogger();
}

void AppFrame::initMenus()
{
    initMenuFile();
    initMenuHelp();
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, APP_FRAME_MENUBAR_FILE);
    menuBar->Append(menuHelp, APP_FRAME_MENUBAR_HELP);
    SetMenuBar(menuBar);
}

void AppFrame::initMenuFile()
{
    menuFile = new wxMenu;
    menuFile->Append(
        static_cast<wxWindowID>(IDs::ID_RESET),
        "&Reset...\tCtrl-R",
        APP_FRAME_STATUS_HINT_RESET);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
}

void AppFrame::initMenuHelp()
{
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
}

void AppFrame::initStatusBar()
{
    CreateStatusBar();
    SetStatusText(APP_FRAME_STATUS_WELCOME);
}

void AppFrame::bindMenuEvents()
{
    Bind(wxEVT_MENU, &AppFrame::OnReset, this, static_cast<wxWindowID>(IDs::ID_RESET));
    Bind(wxEVT_MENU, &AppFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
}

void AppFrame::initTimer()
{
    timestampCtrl = new TimestampCtrl(leftPanel);
    timestampCtrl->SetId(static_cast<wxWindowID>(IDs::ID_TXT_TS));
    timestampCtrl->SetTimerId(static_cast<wxWindowID>(IDs::Timer));
}

void AppFrame::bindTimer()
{
    timestampCtrl->Bind(wxEVT_TIMER, &AppFrame::OnTimer, this, timestampCtrl->GetTimerId());
}

void AppFrame::OnExit(wxCommandEvent &event)
{
    wxLogInfo(APP_LOG_MSG_STOP);
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(
        APP_FRAME_ABOUT_MSGBOX_CONTENT,
        APP_FRAME_ABOUT_MSGBOX_TITLE,
        wxOK | wxICON_INFORMATION);
}

void AppFrame::OnReset(wxCommandEvent &event)
{
    rankListCtrl->Reset();
}

void AppFrame::OnTimer(wxTimerEvent &event)
{
    wxUnusedVar(event);
    timestamp = wxDateTime::Now().FormatTime();
    const char *lts = (const_cast<char *>((const char *)timestamp.mb_str()));
    //GetLogger()->Debug("%s timestamp:%s\n", __PRETTY_FUNCTION__, lts);
    timestampCtrl->SetText(timestamp);
}

void AppFrame::OnButtonAdd(wxCommandEvent &event)
{
    wxUnusedVar(event);
    RankItem r;
    r.timestamp = timestamp;
    r.status = wxString::Format(wxT("%i"), statusId);
    rankListCtrl->AddRank(r);
}

void AppFrame::OnStatusChange(wxCommandEvent &event)
{
    statusId = (event.GetId() - static_cast<wxWindowID>(IDs::ID_RAD_BAD)) + 1;
    GetLogger()->Debug("%s statusId:%d", __PRETTY_FUNCTION__, statusId);
}
