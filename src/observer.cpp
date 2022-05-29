#include <observer.h>

int Observer::static_number_ = 0;

Observer::Observer(Subject &subject) : m_subject(subject)
{
    this->m_subject.Attach(this);
    this->number_ = Observer::static_number_;
}

Observer::~Observer()
{
}

void Observer::Update(const std::string &msg)
{
    m_msg_from_subject = msg;
    if (this->callback != NULL) {
        callback(msg);
    }
}

void Observer::RemoveMeFromTheList()
{
    m_subject.Detach(this);
}