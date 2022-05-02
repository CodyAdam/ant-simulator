#ifndef _ANTHILL_H
#define _ANTHILL_H

#include <Environment.h>
#include <Agent.h>

class Anthill : public Agent
{
private:
  float m_foodQuantity;

public:
  Anthill(Environment *env, const Vector2<float> initPos);
  ~Anthill();
  void depositFood(float quantity);
  float getFoodQuantity() const;
  void update() override;
  void draw() const override;
};

#endif
