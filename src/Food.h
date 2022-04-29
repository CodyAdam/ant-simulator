#ifndef _FOOD_H
#define _FOOD_H

#include <Agent.h>

class Food : public Agent
{
private:
  float m_quantity;
  bool m_needRadiusUpdate = false;

public:
  Food(Environment *env, const Vector2<float> initPos, const float quantity = 200.0f);
  ~Food();
  float getFoodQuantity() const;
  float collectFood(const float quantity);
  void update() override;
  void draw() const override;
};

#endif