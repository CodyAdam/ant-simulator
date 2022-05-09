#ifndef _ORRULE_H
#define _ORRULE_H

#include <AbstractRule.h>

class OrRule : public AbstractRule
{
private:
  AbstractRule *left;
  AbstractRule *right;

public:
  OrRule(AbstractRule *left, AbstractRule *right) : left(left), right(right){};
  ~OrRule()
  {
    delete left;
    delete right;
  }

  virtual bool condition() const
  {
    return left->condition() || right->condition();
  }
  virtual void action()
  {
    if (left->condition())
      left->action();
    else
      right->action();
  };
};

#endif