
#include "fooevent.h"

wxDEFINE_EVENT(FOOEVENT_TYPE, MyFooEvent);

MyFooEvent::MyFooEvent(wxEventType commandType = FOOEVENT_TYPE, int id = 0)
    : wxCommandEvent(commandType, id)
{
}

MyFooEvent::MyFooEvent(const MyFooEvent &event)
    : wxCommandEvent(event)
{
    this->SetPoint(event.GetPoint());
}

wxEvent *MyFooEvent::Clone() const
{
    return new MyFooEvent(*this);
}

wxRealPoint MyFooEvent::GetPoint() const
{
    return m_RealPoint;
}

void MyFooEvent::SetPoint(const wxRealPoint &rp)
{
    m_RealPoint = rp;
}