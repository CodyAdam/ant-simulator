#include <Ant.h>
#include <Food.h>
#include <Timer.h>

Ant::Ant(Anthill *anthill, Vector2<float> initPos)
    : AntBasePheromone(anthill, initPos)
{
}

Ant::~Ant()
{
}

void Ant::update()
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

  if (m_foodQuantity < MAX_FOOD_QUANTITY)
  {
    // look toward visible food if there is any
    std::vector<Food *>
        visible = perceive<Food>(m_direction, FOOD_ANGLE, FOOD_EXTENT, FOOD_MIN_EXTENT);
    if (visible.size() > 0)
    {
      lookAt(visible[0]->getPosition());
    }
    else
    {
      Pheromone *visiblePhero = choosePheromone();
      if (visiblePhero != nullptr)
        lookAt(visiblePhero->getPosition());
      else
      {
        turn(MathUtils::random(-M_PI / 30, M_PI / 30));
      }
    }
    harvest();
    if (m_foodQuantity == MAX_FOOD_QUANTITY)
      flipDirection();
  }
  else
  {
    Pheromone *visiblePhero = choosePheromone();
    if (visiblePhero != nullptr)
      lookAt(visiblePhero->getPosition());
    else
    {
      lookAt(m_anthill->getPosition());
    }
    std::vector<Anthill *>
        visible = perceive<Anthill>();
    for (Anthill *anthill : visible)
    {
      if (anthill == m_anthill)
      {
        m_anthill->depositFood(m_foodQuantity);
        m_foodQuantity = 0.0f;
        flipDirection();
        break;
      }
    }
  }

  move();
}