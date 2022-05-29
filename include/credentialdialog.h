
#ifndef APP_CREDENTIAL_DIALOG_H
#define APP_CREDENTIAL_DIALOG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <mqttbroker.h>

/**
 * @brief Credential dialog control
 *
 */
class CredentialDialog : public wxDialog
{

public:
    explicit CredentialDialog(mqtt_broker_config_t broker_config, wxWindowID wid);
    virtual ~CredentialDialog();
    void show(void);
    void hide(void);
    CredentialDialog *setHost(const std::string &host);
    CredentialDialog *setPort(const std::string &port);
    CredentialDialog *setLogin(const std::string &login);
    CredentialDialog *setPassword(const std::string &passwd);
    CredentialDialog *hydrateConfig(void);
    mqtt_broker_config_t getConfig(void);
    void setSatusMessage(std::string msg);

protected:
    wxPanel *m_panel;
    wxStaticText *m_host_label;
    wxTextCtrl *m_host;
    wxStaticText *m_port_label;
    wxTextCtrl *m_port;
    wxStaticText *m_login_label;
    wxTextCtrl *m_login;
    wxStaticText *m_password_label;
    wxTextCtrl *m_password;
    wxButton *m_ok;
    wxButton *m_close;
    wxStatusBar *m_status_bar;
    mqtt_broker_config_t m_broker_config;
    wxWindowID m_wid;
    CredentialDialog *initStatusBar(void);
    CredentialDialog *initCtrls(void);
    CredentialDialog *initButtons(void);
    CredentialDialog *hydrateCtrls(void);

private:
    static const wxSize _DIALOG_SIZE;
    static const wxSize _BUTTON_SIZE;
    static const wxSize _CTRL_SIZE;
    static const wxString _TITLE;
    static const wxString _EMPTY;
    static const wxString _HOST_LABEL;
    static const wxString _PORT_LABEL;
    static const wxString _LOGIN_LABEL;
    static const wxString _PASSWORD_LABEL;
    static const wxString _OK_LABEL;
    static const wxString _CLOSE_LABEL;
};

#endif