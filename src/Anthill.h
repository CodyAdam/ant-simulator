#ifndef _ANTHILL_H
#define _ANTHILL_H

#include <Environment.h>
#include <Agent.h>

class Anthill : public Agent
{
private:
  float m_foodQuantity;
  float m_totalFoodQuantity;
  int m_type; // 0 = silly, 1 = pheromone, 2 = pheromone with rules

public:
  Anthill(Environment *env, const Vector2<float> initPos, int type = 0);
  ~Anthill();
  void depositFood(float quantity);
  void update() override;
  void draw() const override;
};

#endif
