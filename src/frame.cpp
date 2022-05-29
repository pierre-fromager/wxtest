#include <frame.h>

const wxSize AppFrame::_FRAME_SIZE = wxSize(640, 480);

AppFrame::AppFrame()
    : wxFrame(
          nullptr,
          static_cast<wxWindowID>(IDs::MainWindow),
          wxString(wxGetApp().GetAppName()),
          wxDefaultPosition,
          AppFrame::_FRAME_SIZE)
{
    SetIcon(asset_frame_icon);
    GetLogger()->Debug(APP_LOG_MSG_FRAME_START);
    initMenus()
        ->initStatusBar()
        ->initPanels()
        ->initRadiosStatus()
        ->initListview()
        ->initButtonAdd()
        ->initTimer()
        ->initSizers();
    bindMenuEvents();
    bindTimer();
    bindMqttEvents();
    initCredentialDialog();
    timestampCtrl->TimerStart();
    obsMqttInfo = new Observer(*GetMqtt()->subjectInfo());
    obsMqttInfo->callback = [=](std::string msg) mutable
    {
        m_credential_dlg->setSatusMessage(msg);
        const wxString &wmsg(msg);
        SetStatusText(wmsg);
    };
}

AppFrame *AppFrame::initCredentialDialog(void)
{
    const wxWindowID &widDlg = static_cast<wxWindowID>(IDs::ID_CRED_DLG);
    m_credential_dlg = new CredentialDialog(GetMqtt()->getConfig(), widDlg);
    m_credential_dlg->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnCredentialButtonOk, this, widDlg + 1);
    m_credential_dlg->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnCredentialButtonCancel, this, widDlg + 2);
    // m_credential_dlg->ShowModal();
    m_credential_dlg->show();
    return this;
}

AppFrame::~AppFrame()
{
    GetLogger()->Debug("DESTROY FRAME");
    wxDELETE(timestampCtrl);
    wxDELETE(m_radioBtn1);
    wxDELETE(m_radioBtn2);
    wxDELETE(m_radioBtn3);
    wxDELETE(buttonAdd);
    wxDELETE(rankListCtrl);
    obsMqttInfo->RemoveMeFromTheList();
    wxDELETE(obsMqttInfo);
    wxDELETE(m_credential_dlg);
}

AppFrame *AppFrame::initSizers(void)
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
    /*hboxRight = new wxBoxSizer(wxHORIZONTAL);
    hboxRight->Add(fooButton, 0, wxEXPAND | wxTOP | wxBOTTOM, 1);
    rightPanel->SetSizer(hboxRight);*/
    return this;
}

AppFrame *AppFrame::initRadiosStatus(void)
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
    return this;
}

AppFrame *AppFrame::initPanels(void)
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
    return this;
}

AppFrame *AppFrame::initListview(void)
{
    rankListCtrl = new RankListCtrl(bottomPanel);
    const wxWindowID &rlId = static_cast<wxWindowID>(IDs::ID_RANK_LIST);
    rankListCtrl->SetId(rlId);
    Bind(wxEVT_LIST_ITEM_SELECTED, &AppFrame::OnItemSelect, this, rlId);
    return this;
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

AppFrame *AppFrame::initButtonAdd()
{
    const wxWindowID &bid = static_cast<wxWindowID>(IDs::ID_BUTTON_ADD);
    buttonAdd = new wxButton(leftPanel, bid, _("&Add"));
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppFrame::OnButtonAdd, this, bid);
    return this;
}

FileLogger *AppFrame::GetLogger(void)
{
    return wxGetApp().GetLogger();
}

myMqtt *AppFrame::GetMqtt(void)
{
    return wxGetApp().GetMqtt();
}

AppFrame *AppFrame::initMenus(void)
{
    initMenuFile()->initMenuHelp()->initMenuConfig();
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, APP_FRAME_MENUBAR_FILE);
    menuBar->Append(menuHelp, APP_FRAME_MENUBAR_HELP);
    menuBar->Append(menuConfig, APP_FRAME_MENUBAR_CONFIG);
    SetMenuBar(menuBar);
    return this;
}

AppFrame *AppFrame::initMenuFile(void)
{
    menuFile = new wxMenu;
    menuFile->Append(
        static_cast<wxWindowID>(IDs::ID_RESET),
        "&Reset...\tCtrl-R",
        APP_FRAME_STATUS_HINT_RESET);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    return this;
}

AppFrame *AppFrame::initMenuHelp(void)
{
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    return this;
}

AppFrame *AppFrame::initMenuConfig(void)
{
    menuConfig = new wxMenu;
    menuConfig->Append(
        static_cast<wxWindowID>(IDs::ID_CONF_MQTT),
        "&Mqtt...\tCtrl-M",
        APP_FRAME_MENUBAR_CONFIG_MQTT);
    return this;
}

AppFrame *AppFrame::initStatusBar(void)
{
    CreateStatusBar();
    SetStatusText(APP_FRAME_STATUS_WELCOME);
    return this;
}

void AppFrame::bindMenuEvents(void)
{
    Bind(wxEVT_MENU, &AppFrame::OnReset, this, static_cast<wxWindowID>(IDs::ID_RESET));
    Bind(wxEVT_MENU, &AppFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &AppFrame::OnConfigMqtt, this, static_cast<wxWindowID>(IDs::ID_CONF_MQTT));
}

AppFrame *AppFrame::initTimer(void)
{
    timestampCtrl = new TimestampCtrl(leftPanel);
    timestampCtrl->SetId(static_cast<wxWindowID>(IDs::ID_TXT_TS));
    timestampCtrl->SetTimerId(static_cast<wxWindowID>(IDs::Timer));
    return this;
}

void AppFrame::bindTimer(void)
{
    timestampCtrl->Bind(
        wxEVT_TIMER,
        &AppFrame::OnTimer,
        this,
        timestampCtrl->GetTimerId());
}

void AppFrame::bindMqttEvents(void)
{
    Bind(myEVT_MQTT, &AppFrame::OnMqttEvent, this, wxID_ANY);
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
    GetMqtt()->setPublishTopic(MQTT_TOPIC_PUBLISH_RESET);
    GetMqtt()->publish("1");
    GetMqtt()->publish("0");
}

void AppFrame::OnConfigMqtt(wxCommandEvent &event)
{
    m_credential_dlg->show();
}

void AppFrame::OnTimer(wxTimerEvent &event)
{
    wxUnusedVar(event);
    timestamp = wxDateTime::Now().FormatTime();
    const char *lts = (const_cast<char *>((const char *)timestamp.mb_str()));
    // GetLogger()->Debug("%s timestamp:%s\n", __PRETTY_FUNCTION__, lts);
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

void AppFrame::OnCredentialButtonOk(wxCommandEvent &event)
{
    m_credential_dlg->hydrateConfig();
    mqtt_broker_config_t conf = m_credential_dlg->getConfig();
#ifdef APP_FRAME_DEBUG
    GetLogger()->Debug("%s host :%s", __PRETTY_FUNCTION__, conf.host.c_str());
    GetLogger()->Debug("%s port :%d", __PRETTY_FUNCTION__, conf.port);
    GetLogger()->Debug("%s login :%s", __PRETTY_FUNCTION__, conf.login.c_str());
    GetLogger()->Debug("%s passwd :%s", __PRETTY_FUNCTION__, conf.password.c_str());
#endif
    
    if (GetMqtt()->isConnected())
    {
        // m_credential_dlg->setSatusMessage("Disconnecting from broker...");
        GetMqtt()->disconnect();
    }
    GetMqtt()
        ->setHost(conf.host)
        ->setPort(conf.port)
        ->setUsername(conf.login)
        ->setPassword(conf.password)
        ->connect();
    if (GetMqtt()->isConnected())
    {
        // m_credential_dlg->setSatusMessage("Connected to broker");
        //m_credential_dlg->hide();
    }
    
}

void AppFrame::OnCredentialButtonCancel(wxCommandEvent &event)
{
    m_credential_dlg->hide();
}

void AppFrame::OnStatusChange(wxCommandEvent &event)
{
    wxRadioButton *radio = static_cast<wxRadioButton *>(FindWindowById(event.GetId()));
    radio->SetValue(true);
    statusId = (event.GetId() - static_cast<wxWindowID>(IDs::ID_RAD_BAD)) + 1;
    GetMqtt()->setPublishTopic(MQTT_TOPIC_PUBLISH_STATUS);
    GetMqtt()->publish(std::to_string(statusId));
    GetLogger()->Debug("%s statusId:%d", __PRETTY_FUNCTION__, statusId);
}

void AppFrame::OnMqttEvent(MyMqttEvent &ev)
{
    GetLogger()->Debug(
        "%s id=%d topic=%s payload=%s",
        __PRETTY_FUNCTION__,
        ev.GetId(),
        (const_cast<char *>((const char *)ev.GetTopic().c_str())),
        (const_cast<char *>((const char *)ev.GetPayload().c_str())));

    if (ev.GetTopic().compare(MQTT_TOPIC_CONTROL_STATUS) == 0)
    {
        const int radioOffset = std::stoi(ev.GetPayload()) - 1;
        if (radioOffset >= 0 && radioOffset < 3)
        {
            wxCommandEvent event(
                wxEVT_COMMAND_RADIOBUTTON_SELECTED,
                static_cast<wxWindowID>(IDs::ID_RAD_BAD) + radioOffset);
            ProcessWindowEvent(event);
        }
    }

    if (ev.GetTopic().compare(MQTT_TOPIC_CONTROL_RESET) == 0)
    {
        if (ev.GetPayload().compare("1") == 0)
        {
            wxCommandEvent event(
                wxEVT_COMMAND_MENU_SELECTED,
                static_cast<wxWindowID>(IDs::ID_RESET));
            ProcessWindowEvent(event);
        }
    }

    if (ev.GetTopic().compare(MQTT_TOPIC_CONTROL_ADD) == 0)
    {
        if (ev.GetPayload().compare("1") == 0)
        {
            wxCommandEvent event(
                wxEVT_COMMAND_BUTTON_CLICKED,
                static_cast<wxWindowID>(IDs::ID_BUTTON_ADD));
            ProcessWindowEvent(event);
        }
    }
}
