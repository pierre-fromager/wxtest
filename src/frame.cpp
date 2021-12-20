#include "frame.h"

AppFrame::AppFrame(wxApp *app)
    : wxFrame(
          nullptr,
          static_cast<wxWindowID>(IDs::MainWindow),
          wxString(app->GetAppDisplayName()),
          wxDefaultPosition,
          wxSize(640, 480))
{
    app->SetAppDisplayName(APP_FRAME_TITLE);
    initMenus();
    initStatusBar();
    bindMenuEvents();
    initPanels();
    initRadiosStatus();
    initListview();
    initButton();
    initTimer();
    bindTimer();
    initSizers();
    timestampCtrl->TimerStart();
}

void AppFrame::initSizers()
{
    vboxLeft = new wxBoxSizer(wxVERTICAL);
    vboxLeft->Add(timestampCtrl, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    vboxLeft->Add(m_radioBtn1, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    vboxLeft->Add(m_radioBtn2, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    vboxLeft->Add(m_radioBtn3, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    vboxLeft->Add(buttonAdd, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    leftPanel->SetSizer(vboxLeft);
    vboxBottom = new wxBoxSizer(wxVERTICAL);
    vboxBottom->Add(rankListCtrl, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    bottomPanel->SetSizer(vboxBottom);
    //hboxRight = new wxBoxSizer(wxHORIZONTAL);
    //hboxRight->Add(timestampCtrl, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    //rightPanel->SetSizer(hboxRight);
}

void AppFrame::initRadiosStatus()
{
    const wxSize &rs = wxSize(20, 20);
    m_radioBtn1 = new wxRadioButton(
        leftPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_BAD),
        _("&Bad"),
        wxDefaultPosition,
        rs,
        wxRB_GROUP);
    m_radioBtn1->SetValue(true);
    Bind(
        wxEVT_RADIOBUTTON,
        &AppFrame::OnStatusChange,
        this,
        static_cast<wxWindowID>(AppFrame::IDs::ID_RAD_BAD));
    m_radioBtn2 = new wxRadioButton(
        leftPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_MEDIUM),
        _("&Medium"),
        wxDefaultPosition,
        rs,
        0);
    Bind(
        wxEVT_RADIOBUTTON,
        &AppFrame::OnStatusChange,
        this,
        static_cast<wxWindowID>(IDs::ID_RAD_MEDIUM));
    m_radioBtn3 = new wxRadioButton(
        leftPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_GOOD),
        _("&Good"),
        wxDefaultPosition,
        rs,
        0);
    Bind(
        wxEVT_RADIOBUTTON,
        &AppFrame::OnStatusChange,
        this,
        static_cast<wxWindowID>(IDs::ID_RAD_GOOD));
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
    rankListCtrl->SetId(static_cast<wxWindowID>(IDs::ID_RANK_LIST));
    Bind(
        wxEVT_LIST_ITEM_SELECTED,
        &AppFrame::OnItemSelect,
        this,
        static_cast<wxWindowID>(IDs::ID_RANK_LIST));
}

void AppFrame::OnItemSelect(wxListEvent &event)
{
    const RankItem &r = rankListCtrl->GetRank(event.GetIndex());
#ifdef APP_FRAME_DEBUG
    std::cout << "OnItemSelect Timestamp:" << r.timestamp << std::endl;
#endif
}

void AppFrame::initButton()
{
    buttonAdd = new wxButton(
        leftPanel,
        static_cast<wxWindowID>(IDs::ID_BUTTON),
        _("&Add"));
    Bind(
        wxEVT_COMMAND_BUTTON_CLICKED,
        &AppFrame::OnPress,
        this,
        static_cast<wxWindowID>(IDs::ID_BUTTON));
}

void AppFrame::initStatusBar()
{
    CreateStatusBar();
    SetStatusText(APP_FRAME_STATUS_WELCOME);
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
    timestampCtrl->Bind(
        wxEVT_TIMER,
        &AppFrame::OnTimer,
        this,
        timestampCtrl->GetTimerId());
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

void AppFrame::OnReset(wxCommandEvent &event)
{
    rankListCtrl->Reset();
}

void AppFrame::OnTimer(wxTimerEvent &event)
{
    wxUnusedVar(event);
    timestamp = wxDateTime::Now().FormatTime();
#ifdef APP_FRAME_DEBUG
    //std::cout << timestamp << std::endl;
#endif
    timestampCtrl->SetText(timestamp);
}

void AppFrame::OnPress(wxCommandEvent &event)
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
#ifdef APP_FRAME_DEBUG
    std::cout << statusId << std::endl;
#endif
}