
#include "timestampctrl.h"

TimestampCtrl::TimestampCtrl(wxWindow *parent) : wxPanel(
                                                     parent,
                                                     wxID_ANY,
                                                     wxDefaultPosition,
                                                     wxSize(TSCTRL_MINW, TSCTRL_MINH))
{
    GetSize(&w, &h);
    SetBackgroundColour(TSCTRL_BGC);
    const wxPoint &p = wxPoint(w / TSCTRL_PO, h / TSCTRL_PO);
    const wxSize &s = wxSize(w - TSCTRL_SO, h - TSCTRL_SO);

    m_text = new wxStaticText(
        this,
        wxID_ANY,
        TSCTRL_DFLT_LABEL,
        p,
        s,
        wxALIGN_CENTRE_HORIZONTAL);
    m_text->SetForegroundColour(TSCTRL_FGC);
    wxFont tsFont(
        TSCTRL_FONTSIZE,
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_BOLD,
        false,
        _T(TSCTRL_FONTNAME),
        wxFONTENCODING_DEFAULT);
    m_text->SetFont(tsFont);
}

TimestampCtrl::~TimestampCtrl()
{
    wxDELETE(m_text);
}

void TimestampCtrl::SetText(const wxString &text)
{
    m_text->SetLabel(text);
}

void TimestampCtrl::SetTimerId(const wxWindowID &id)
{
    timer = new wxTimer(this, id);
}

wxWindowID TimestampCtrl::GetTimerId()
{
    return timer->GetId();
}

void TimestampCtrl::TimerStart()
{
    timer->Start(TSCTRL_TIMER_DELTA, wxTIMER_CONTINUOUS);
}

void TimestampCtrl::TimerStop()
{
    timer->Stop();
}
