#ifndef _FINDANTHILLRULE_H
#define _FINDANTHILLRULE_H

#include <AbstractAntRule.h>

class FindAnthillRule : public AbstractAntRule
{
private:
public:
  FindAnthillRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~FindAnthillRule() {}

  bool condition() const override
  {
    // la fourmi transporte de la nourriture et ne se trouve pas sur son nid

    return ant->getFoodQuantity() == ant->MAX_FOOD_QUANTITY;
  }

  void action() override
  {
    Pheromone *phero = ant->choosePheromone();
    if (phero != nullptr)
      ant->lookAt(phero->getPosition());
    else
      ant->lookAt(ant->getAnthill()->getPosition());
  }
};

#endif