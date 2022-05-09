#ifndef _HARVESTRULE_H
#define _HARVESTRULE_H

#include <AbstractAntRule.h>
#include <Food.h>

class HarvestRule : public AbstractAntRule
{
private:
public:
  HarvestRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~HarvestRule() {}

  bool condition() const override
  {
    // la fourmi ne transporte pas de nourriture et se trouve sur de la nourriture
    std::vector<Food *> food = ant->perceive<Food>();
    return ant->getFoodQuantity() < ant->MAX_FOOD_QUANTITY && food.size() > 0;
  }

  void action() override
  {
    ant->harvest();
    ant->flipDirection();
  }
};

#endif