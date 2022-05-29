
#include <subject.h>

Subject::~Subject()
{
}

void Subject::Attach(IObserver *observer)
{
    list_observer_.push_back(observer);
}

void Subject::Detach(IObserver *observer)
{
    list_observer_.remove(observer);
}

void Subject::Notify()
{
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    while (iterator != list_observer_.end())
    {
        (*iterator)->Update(message_);
        ++iterator;
    }
}

void Subject::CreateMessage(std::string message)
{
    this->message_ = message;
    Notify();
}
