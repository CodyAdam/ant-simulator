#ifndef _FINDPHERORULE_H
#define _FINDPHERORULE_H

#include <AbstractAntRule.h>
#include <Pheromone.h>

class FindPheroRule : public AbstractAntRule
{
private:
public:
  FindPheroRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~FindPheroRule() {}

  bool condition() const override
  {
    // la fourmi ne transporte pas de nourriture mais perçoit la nourriture
    Pheromone *phero = ant->choosePheromone();
    return phero != nullptr && ant->getFoodQuantity() < ant->MAX_FOOD_QUANTITY;
  }

  void action() override
  {
    Pheromone *phero = ant->choosePheromone();
    ant->lookAt(phero->getPosition());
  }
};

#endif