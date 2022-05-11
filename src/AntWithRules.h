#ifndef _ANTWITHRULES_H
#define _ANTWITHRULES_H

#include <AntBasePheromone.h>
#include <AbstractAntRule.h>
#include <OrRule.h>
#include <HarvestRule.h>
#include <FindFoodRule.h>
#include <FindPheroRule.h>
#include <DepositRule.h>
#include <RandomMoveRule.h>
#include <FindAnthillRule.h>

class AntWithRules : AntBasePheromone
{
private:
  AbstractRule *rule;

public:
  AntWithRules(Anthill *anthill, Vector2<float> initPos) : AntBasePheromone(anthill, initPos)

  {
    // order : HarvestRule, FindFoodRule, FindPheroRule, DepositRule, RandomMoveRule, FindAnthillRule

    rule = new OrRule(
        new HarvestRule(this),
        new OrRule(
            new FindFoodRule(this),
            new OrRule(
                new FindPheroRule(this),
                new OrRule(
                    new DepositRule(this),
                    new OrRule(
                        new RandomMoveRule(this),
                        new FindAnthillRule(this))))));
  }
  ~AntWithRules()
  {
    delete rule;
  }

  void update() override
  {
    if (m_lifeTime > 0.0f)
      m_lifeTime -= 1;
    else
      setStatus(Status::destroy);

    // Put pheromone, and more if the ant has food and if close to anthill
    float dist = getAnthill()->getPosition().distance(getPosition());
    float amout = std::max(100.0f - 0.2f * dist - 0.0011f * dist * dist, 0.0f);
    if (m_foodQuantity > 0)
      putPheromone(100.0f + amout);
    else
      putPheromone(10.0f + amout);

    if (rule->condition())
      rule->action();

    move();
  }
};

#endif