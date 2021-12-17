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
    initPanel();
    initListview();
    initButton();
    initGrid();
    vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 1, wxEXPAND | wxTOP | wxBOTTOM, 3);
    panel->SetSizer(vbox);
    initTimer();
    bindTimer();
    timer->Start(APP_FRAME_TIMER_DELTA, wxTIMER_CONTINUOUS);
}

void AppFrame::initPanel()
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    panel->SetBackgroundColour(wxColour(100, 100, 200));
}

void AppFrame::initListview()
{
    listview = new wxListCtrl(
        panel,
        ID_List,
        wxDefaultPosition,
        wxDefaultSize,
        wxLC_REPORT);
    wxListItem col0, col1, col2;
    col0.SetId(0);
    col0.SetText(_("Index"));
    col0.SetWidth(
        wxLIST_AUTOSIZE_USEHEADER);
    listview->InsertColumn(0, col0);

    col1.SetId(1);
    col1.SetText(_("Timestamp"));
    col1.SetWidth(
        wxLIST_AUTOSIZE_USEHEADER);
    listview->InsertColumn(1, col1);

    col2.SetId(2);
    col2.SetText(_("Status"));
    col2.SetWidth(
        wxLIST_AUTOSIZE_USEHEADER);
    listview->InsertColumn(2, col2);

    Bind(wxEVT_COMMAND_LIST_COL_CLICK, &AppFrame::OnColSelect, this, ID_List);
    Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AppFrame::OnItemSelect, this, ID_List);
}

void AppFrame::OnColSelect(wxListEvent &event)
{
    SortInfoStruct m_sortInfo(listview);
    m_sortInfo.column = event.GetColumn();
    m_sortInfo.direction = !m_sortInfo.direction;
    m_sortInfo.type = static_cast<int>(SortInfoStruct::SortInfoType::string);
    listview->SortItems(&m_sortInfo.sortlist, (long)&m_sortInfo);
}

void AppFrame::OnItemSelect(wxListEvent &event)
{
    std::cout << "OnItemSelect"
              << " Id:" << event.GetId()
              << " Index:" << event.GetIndex()
              << std::endl;
}

void AppFrame::initGrid()
{
    grid = new wxGridSizer(1, 2, 0, 3);
    grid->Add(button, 0, wxEXPAND);
    grid->Add(listview, 0, wxEXPAND);
}

void AppFrame::initButton()
{
    button = new wxButton(panel, ID_Button, wxT("Press"));
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnPress, this, ID_Button);
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
        ID_Hello,
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
    Bind(wxEVT_MENU, &AppFrame::OnReset, this, ID_Hello);
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
    listview->DeleteAllItems();
    itemIndex = 0;
}

void AppFrame::OnTimer(wxTimerEvent &evt)
{
    wxUnusedVar(evt);
    timestamp = wxDateTime::Now().FormatTime();
    button->SetLabel(timestamp);
    SetStatusText(timestamp);
}

void AppFrame::OnPress(wxCommandEvent &evt)
{
    wxUnusedVar(evt);
    wxListItem item;
    item.SetId(itemIndex);
    item.SetText(wxString::Format(wxT("%i"), itemIndex));
    item.SetColumn(0);
    long index = listview->InsertItem(item);
    listview->SetItem(index, 1, timestamp);
    itemIndex++;
}