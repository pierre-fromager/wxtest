#ifndef APP_FOOEVENT_H
#define APP_FOOEVENT_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyFooEvent : public wxCommandEvent
{

public:
    MyFooEvent(wxEventType commandType, int id);
    MyFooEvent(const MyFooEvent &event);
    virtual wxEvent *Clone() const override;
    wxRealPoint GetPoint() const;
    void SetPoint(const wxRealPoint &rp);

private:
    wxRealPoint m_RealPoint;
};

wxDECLARE_EVENT(FOOEVENT_TYPE, MyFooEvent);

#endif