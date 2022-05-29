
#include <credentialdialog.h>

const wxString CredentialDialog::_TITLE = wxString("Credentials");
const wxString CredentialDialog::_HOST_LABEL = wxString("Host");
const wxString CredentialDialog::_PORT_LABEL = wxString("Port");
const wxString CredentialDialog::_LOGIN_LABEL = wxString("Login");
const wxString CredentialDialog::_PASSWORD_LABEL = wxString("Password");
const wxString CredentialDialog::_OK_LABEL = wxString("Ok");
const wxString CredentialDialog::_CLOSE_LABEL = wxString("Close");
const wxString CredentialDialog::_EMPTY = wxString("");
const wxSize CredentialDialog::_DIALOG_SIZE = wxSize(250, 400);
const wxSize CredentialDialog::_BUTTON_SIZE = wxSize(70, 30);
const wxSize CredentialDialog::_CTRL_SIZE = wxSize(220, 35);

CredentialDialog::CredentialDialog(mqtt_broker_config_t broker_config, wxWindowID wid) : wxDialog(
                                                                                             NULL,
                                                                                             wid,
                                                                                             CredentialDialog::_TITLE,
                                                                                             wxDefaultPosition,
                                                                                             CredentialDialog::_DIALOG_SIZE),
                                                                                         m_broker_config(broker_config),
                                                                                         m_wid(wid)
{
    m_panel = new wxPanel(this, -1);
    initCtrls()->hydrateCtrls()->initButtons()->initStatusBar();
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(m_ok, 1);
    hbox->Add(m_close, 1, wxLEFT, 5);
    vbox->Add(m_panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(m_status_bar, 1, wxEXPAND | wxALL, 0);
    SetSizer(vbox);
    Centre();
}

CredentialDialog::~CredentialDialog()
{
    // Destroy();
}

CredentialDialog *CredentialDialog::initStatusBar(void)
{
    m_status_bar = new wxStatusBar(this);
    std::vector statusWidths = {240};
    std::vector statusStyles = {wxSB_HORIZONTAL | wxSB_FLAT};
    m_status_bar->SetFieldsCount(statusWidths.size());
    m_status_bar->SetStatusWidths(statusWidths.size(), statusWidths.data());
    m_status_bar->SetStatusStyles(statusStyles.size(), statusStyles.data());
    m_status_bar->SetStatusText("Set your mqtt config");
    return this;
}

void CredentialDialog::setSatusMessage(std::string msg)
{
    wxString wstr(msg);
    m_status_bar->SetStatusText(wstr);
}

CredentialDialog *CredentialDialog::initCtrls(void)
{
    const int dy = 60;
    int x, y;
    x = y = 10;
    int yp = 30;
    m_host_label = new wxStaticText(m_panel, -1, CredentialDialog::_HOST_LABEL, wxPoint(x, y));
    m_host = new wxTextCtrl(m_panel, -1, CredentialDialog::_EMPTY, wxPoint(x, yp), CredentialDialog::_CTRL_SIZE);
    m_port_label = new wxStaticText(m_panel, -1, CredentialDialog::_PORT_LABEL, wxPoint(x, y += dy));
    // todo : implement validator
    // see : https://docs.wxwidgets.org/3.0/overview_validator.html
    /*0, wxTextValidator(wxFILTER_NUMERIC, wxAtoi(&m_broker_config.port*/
    m_port = new wxTextCtrl(
        m_panel,
        -1,
        CredentialDialog::_EMPTY,
        wxPoint(x, yp += dy),
        CredentialDialog::_CTRL_SIZE);
    m_login_label = new wxStaticText(m_panel, -1, CredentialDialog::_LOGIN_LABEL, wxPoint(x, y += dy));
    m_login = new wxTextCtrl(m_panel, -1, CredentialDialog::_EMPTY, wxPoint(x, yp += dy), CredentialDialog::_CTRL_SIZE);
    m_password_label = new wxStaticText(m_panel, -1, CredentialDialog::_PASSWORD_LABEL, wxPoint(x, y += dy));
    m_password = new wxTextCtrl(m_panel, -1, CredentialDialog::_EMPTY, wxPoint(x, yp += dy), CredentialDialog::_CTRL_SIZE);
    m_password->SetWindowStyle(wxTE_PASSWORD);
    m_password->Refresh();
    return this;
}

CredentialDialog *CredentialDialog::hydrateCtrls(void)
{
    m_host->SetValue(m_broker_config.host);
    m_port->SetValue(wxString::Format(wxT("%i"), m_broker_config.port));
    m_login->SetValue(m_broker_config.login);
    m_password->SetValue(m_broker_config.password);
    return this;
}

CredentialDialog *CredentialDialog::hydrateConfig(void)
{
    m_broker_config.host = std::string(m_host->GetValue().c_str());
    m_broker_config.port = wxAtoi(m_port->GetValue());
    m_broker_config.login = std::string(m_login->GetValue().c_str());
    m_broker_config.password = std::string(m_password->GetValue().c_str());
    return this;
}

mqtt_broker_config_t CredentialDialog::getConfig(void)
{
    return m_broker_config;
}

CredentialDialog *CredentialDialog::initButtons(void)
{
    m_ok = new wxButton(this, m_wid + 1, CredentialDialog::_OK_LABEL, wxDefaultPosition, CredentialDialog::_BUTTON_SIZE);
    m_close = new wxButton(this, m_wid + 2, CredentialDialog::_CLOSE_LABEL, wxDefaultPosition, CredentialDialog::_BUTTON_SIZE);
    return this;
}

void CredentialDialog::show(void)
{
    this->Show(true);
}

void CredentialDialog::hide(void)
{
    this->Show(false);
}

CredentialDialog *CredentialDialog::setHost(const std::string &host)
{
    m_host->ChangeValue(host.c_str());
    return this;
}

CredentialDialog *CredentialDialog::setPort(const std::string &port)
{
    m_port->ChangeValue(port.c_str());
    return this;
}

CredentialDialog *CredentialDialog::setLogin(const std::string &login)
{
    m_login->ChangeValue(login.c_str());
    return this;
}

CredentialDialog *CredentialDialog::setPassword(const std::string &passwd)
{
    m_password->ChangeValue(passwd.c_str());
    return this;
}
