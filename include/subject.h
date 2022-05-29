
#ifndef SUBJECT_H
#define SUBJECT_H

#include <observable.h>

/**
 * @brief class for subject
 *
 */
class Subject : public ISubject
{
public:
  virtual ~Subject();
  void Attach(IObserver *observer);
  void Detach(IObserver *observer);
  void Notify();
  void CreateMessage(std::string message = "Empty");

private:
  std::list<IObserver *> list_observer_;
  std::string message_;
};

#endif