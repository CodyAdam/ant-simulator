#ifndef _FINDFOODRULE_H
#define _FINDFOODRULE_H

#include <AbstractAntRule.h>
#include <Food.h>

class FindFoodRule : public AbstractAntRule
{
private:
public:
  FindFoodRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~FindFoodRule() {}

  bool condition() const override
  {
    // la fourmi ne transporte pas de nourriture mais perçoit la nourriture
    std::vector<Food *> food = ant->perceive<Food>(ant->getDirection(), ant->FOOD_ANGLE, ant->FOOD_EXTENT, ant->FOOD_MIN_EXTENT);
    return ant->getFoodQuantity() < ant->MAX_FOOD_QUANTITY && food.size() > 0;
  }

  void action() override
  {
    std::vector<Food *> food = ant->perceive<Food>(ant->getDirection(), ant->FOOD_ANGLE, ant->FOOD_EXTENT, ant->FOOD_MIN_EXTENT);
    ant->lookAt(food[0]->getPosition());
  }
};

#endif