
#ifndef OBSERVER_H
#define OBSERVER_H

#include <observable.h>
#include <subject.h>
#include <algorithm>
#include <functional>

/**
 * @brief class for observer
 *
 */
class Observer : public IObserver
{
public:
  explicit Observer(Subject &subject);
  virtual ~Observer();
  void Update(const std::string &msge_from_subject);
  void RemoveMeFromTheList();
  std::function<void(std::string)> callback = nullptr;

private:
  std::string m_msg_from_subject;
  Subject &m_subject;
  static int static_number_;
  int number_;
};

#endif