#ifndef _DEPOSITRULE_H
#define _DEPOSITRULE_H

#include <AbstractAntRule.h>

class DepositRule : public AbstractAntRule
{
private:
public:
  DepositRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~DepositRule() {}

  bool condition() const override
  {
    // la fourmi transporte de la nourriture et se trouve sur son nid
    std::vector<Anthill *> ah = ant->perceive<Anthill>();
    if (ah.size() > 0 && ant->getFoodQuantity() == ant->MAX_FOOD_QUANTITY)
      for (Anthill *a : ah)
        if (a == ant->getAnthill())
          return true;
    return false;
  }

  void action() override
  {
    std::vector<Anthill *> ah = ant->perceive<Anthill>();
    for (Anthill *a : ah)
      if (a == ant->getAnthill())
      {
        a->depositFood(ant->getFoodQuantity());
        ant->setFoodQuantity(0);
        ant->flipDirection();
        return;
      }
  }
};

#endif