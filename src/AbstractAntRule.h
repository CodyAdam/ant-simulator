#ifndef _ABSTRACTANTRULE_H
#define _ABSTRACTANTRULE_H

#include <AbstractRule.h>
#include <AntBasePheromone.h>

class AbstractAntRule : public AbstractRule
{
protected:
  AntBasePheromone *ant;

public:
  AbstractAntRule(AntBasePheromone *ant) : ant(ant) {}
  ~AbstractAntRule() {}
};

#endif