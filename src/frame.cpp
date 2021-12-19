#include "frame.h"

AppFrame::AppFrame(wxApp *app)
    : wxFrame(
          nullptr,
          static_cast<wxWindowID>(IDs::MainWindow),
          wxString(app->GetAppDisplayName()),
          wxDefaultPosition,
          wxSize(480, 300))
{
    app->SetAppDisplayName(APP_FRAME_TITLE);
    initMenus();
    initStatusBar();
    bindMenuEvents();
    initPanels();
    initRadiosStatus();
    initListview();
    initButton();
    initSizers();
    initTimer();
    bindTimer();
    timer->Start(APP_FRAME_TIMER_DELTA, wxTIMER_CONTINUOUS);
}

void AppFrame::initSizers(){
  vboxLeft = new wxBoxSizer(wxVERTICAL);
    vboxLeft->Add(button, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    leftPanel->SetSizer(vboxLeft);
    vboxBottom = new wxBoxSizer(wxVERTICAL);
    vboxBottom->Add(rankListCtrl, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    bottomPanel->SetSizer(vboxBottom);
    hboxRight = new wxBoxSizer(wxHORIZONTAL);
    hboxRight->Add(m_radioBtn1, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    hboxRight->Add(m_radioBtn2, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    hboxRight->Add(m_radioBtn3, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    rightPanel->SetSizer(hboxRight);
}

void AppFrame::initRadiosStatus()
{
    m_radioBtn1 = new wxRadioButton(
        rightPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_BAD),
        wxT("Bad"),
        wxDefaultPosition,
        wxDefaultSize,
        wxRB_GROUP);
    m_radioBtn1->SetValue(true);
    Bind(
        wxEVT_RADIOBUTTON,
        &AppFrame::OnStatusChange,
        this,
        static_cast<wxWindowID>(IDs::ID_RAD_BAD));
    m_radioBtn2 = new wxRadioButton(
        rightPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_MEDIUM),
        wxT("Medium"),
        wxDefaultPosition,
        wxDefaultSize,
        0);
    Bind(
        wxEVT_RADIOBUTTON,
        &AppFrame::OnStatusChange,
        this,
        static_cast<wxWindowID>(IDs::ID_RAD_MEDIUM));
    m_radioBtn3 = new wxRadioButton(
        rightPanel,
        static_cast<wxWindowID>(IDs::ID_RAD_GOOD),
        wxT("Good"),
        wxDefaultPosition,
        wxDefaultSize,
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
        wxSP_BORDER | wxSP_LIVE_UPDATE);
    wxSplitterWindow *right_splitter = new wxSplitterWindow(
        splitter,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_BORDER | wxSP_LIVE_UPDATE);
    leftPanel = new wxPanel(splitter);
    rightPanel = new wxPanel(right_splitter);
    bottomPanel = new wxPanel(right_splitter);
    leftPanel->SetBackgroundColour(wxColor(200, 100, 100));
    rightPanel->SetBackgroundColour(wxColor(100, 200, 100));
    bottomPanel->SetBackgroundColour(wxColor(200, 200, 100));
    right_splitter->SetMinimumPaneSize(100);
    right_splitter->SplitHorizontally(rightPanel, bottomPanel);
    right_splitter->SetSashGravity(0);
    splitter->SetMinimumPaneSize(100);
    splitter->SplitVertically(leftPanel, right_splitter);
}

void AppFrame::initListview()
{
    rankListCtrl = new RankListCtrl(bottomPanel);
}

void AppFrame::OnItemSelect(wxListEvent &event)
{
    std::cout << "OnItemSelect"
              << " Id:" << event.GetId()
              << " Index:" << event.GetIndex()
              << std::endl;
}

void AppFrame::initButton()
{
    button = new wxButton(
        leftPanel,
        static_cast<wxWindowID>(IDs::ID_BUTTON),
        wxT("Press"));
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
        APP_FRAME_STATUS_OVERHELP);
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
    timer = new wxTimer(this, static_cast<int>(IDs::Timer));
}

void AppFrame::bindTimer()
{
    Bind(wxEVT_TIMER, &AppFrame::OnTimer, this, timer->GetId());
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
    button->SetLabel(timestamp);
    SetStatusText(timestamp);
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
    //std::cout << statusId << std::endl;
}