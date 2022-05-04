#ifndef _PHEROMONE_H_
#define _PHEROMONE_H_

#include <Agent.h>
#include <Vector2.h>

class Pheromone : public Agent
{
private:
  float m_strength;

  static const float PHERO_RADIUS;

public:
  Pheromone(Environment *environment, const Vector2<float> &position, float strength);
  ~Pheromone();

  void addStrength(float amount);
  float getStrength() const;
  void update() override;
  void draw() const override;
};

#endif