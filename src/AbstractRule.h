#ifndef _ABSTRACTRULE_H
#define _ABSTRACTRULE_H

class AbstractRule
{
private:
public:
  AbstractRule() {}
  virtual ~AbstractRule() {}

  virtual bool condition() const = 0;
  virtual void action() = 0;
};

#endif