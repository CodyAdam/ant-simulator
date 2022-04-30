#include <AntBasePheromone.h>
#include <Pheromone.h>
#include <MathUtils.h>

AntBasePheromone::AntBasePheromone(Anthill *anthill, Vector2<float> initPos, const float speed)
    : AntBase(anthill, initPos, speed) {}

AntBasePheromone::~AntBasePheromone() {}

float AntBasePheromone::PHERO_EXTENT = 8.0f;

void AntBasePheromone::putPheromone(float q)
{
  std::vector<Pheromone *> pheros = perceive<Pheromone>();
  if (pheros.size() > 0)
    for (Pheromone *phero : pheros)
    {
      phero->addStrength(q);
    }
  else
    new Pheromone(getEnvironment(), getPosition(), q);
}

Pheromone *AntBasePheromone::choosePheromone() const
{
  std::vector<Pheromone *> pheros = perceive<Pheromone>(m_direction, CONE_ANGLE, PHERO_EXTENT, 3.0f);
  if (pheros.size() > 0)
  {
    std::vector<float> weights = {};
    for (Pheromone *phero : pheros)
      weights.push_back(phero->getStrength());
    return pheros[MathUtils::randomChoose(weights)];
  }
  else
    return nullptr;
}