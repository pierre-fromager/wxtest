
#include "fooevent.h"

wxDEFINE_EVENT(myEVT_FOO, MyFooEvent);

MyFooEvent::MyFooEvent(
    wxEventType evType = myEVT_FOO,
    int id = 0) : wxCommandEvent(evType, id) {}

MyFooEvent::MyFooEvent(const MyFooEvent &ev) : wxCommandEvent(ev)
{
    this->SetPoint(ev.GetPoint());
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