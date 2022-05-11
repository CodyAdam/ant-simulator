#ifndef _RANDOMMOVERULE_H
#define _RANDOMMOVERULE_H

#include <AbstractAntRule.h>
#include <Food.h>

class RandomMoveRule : public AbstractAntRule
{
private:
public:
  RandomMoveRule(AntBasePheromone *ant) : AbstractAntRule(ant){};
  ~RandomMoveRule() {}

  bool condition() const override
  {
    // la fourmi ne transporte pas de nourriture mais perçoit la nourriture
    Pheromone *phero = ant->choosePheromone();
    return phero == nullptr && ant->getFoodQuantity() < ant->MAX_FOOD_QUANTITY;
  }

  void action() override
  {
    ant->turn(MathUtils::random(-M_PI / 30, M_PI / 30));
  }
};

#endif