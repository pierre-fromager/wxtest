#ifndef APP_FOOEVENT_H
#define APP_FOOEVENT_H

class MyFooEvent;
wxDEFINE_EVENT(FOOEVENT_TYPE, MyFooEvent);

typedef void (wxEvtHandler::*MyFooEventFunction)(MyFooEvent &);
#define MyFooEventHandler(func) wxEVENT_HANDLER_CAST(MyFooEventFunction, func)

class MyFooEvent : public wxCommandEvent
{
public:
    MyFooEvent(wxEventType commandType = FOOEVENT_TYPE, int id = 0)
        : wxCommandEvent(commandType, id) {}

    // You *must* copy here the data to be transported
    MyFooEvent(const MyFooEvent &event)
        : wxCommandEvent(event) { this->SetPoint(event.GetPoint()); }

    // Required for sending with wxPostEvent()
    wxEvent *Clone() const { return new MyFooEvent(*this); }

    wxRealPoint GetPoint() const { return m_RealPoint; }
    void SetPoint(const wxRealPoint &rp) { m_RealPoint = rp; }

private:
    wxRealPoint m_RealPoint;
};

#endif