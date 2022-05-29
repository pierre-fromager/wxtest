
#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <iostream>
#include <list>
#include <string>

/**
 * @brief Interface for observer
 *
 */
class IObserver
{
public:
  virtual ~IObserver(){};
  virtual void Update(const std::string &message_from_subject) = 0;
};

/**
 * @brief Interface for subject
 *
 */
class ISubject
{
public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

#endif