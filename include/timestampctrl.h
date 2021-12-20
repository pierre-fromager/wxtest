
#ifndef APP_TIMESTAMPCTRL_H
#define APP_TIMESTAMPCTRL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#define TSCTRL_FGC *wxGREEN
#define TSCTRL_BGC *wxBLACK
#define TSCTRL_MINW 110
#define TSCTRL_MINH 22

#define TSCTRL_PO 8
#define TSCTRL_SO (TSCTRL_PO / 2)

#define TSCTRL_FONTNAME "Sans"
#define TSCTRL_FONTSIZE 12
#define TSCTRL_DFLT_LABEL "00:00:00"

#define TSCTRL_TIMER_DELTA 1000

class TimestampCtrl : public wxPanel
{

public:
    TimestampCtrl(wxWindow *parent);
    virtual ~TimestampCtrl();
    void SetText(const wxString &text);
    void SetTimerId(const wxWindowID &id);
    wxWindowID GetTimerId();
    void TimerStart();
    void TimerStop();

private:
    wxStaticText *m_text = nullptr;
    wxTimer *timer = nullptr;
    int w, h;
};

#endif