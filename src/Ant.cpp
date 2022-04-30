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
    m_lifeTime -= Timer::dt();
  else
    setStatus(Status::destroy);

  if (m_foodQuantity > 0)
    putPheromone(100.0f);
  else
    putPheromone(10.0f);

  if (m_foodQuantity < MAX_FOOD_QUANTITY)
  {
    // look toward visible food if there is any
    std::vector<Food *>
        visible = perceive<Food>(m_direction, CONE_ANGLE, CONE_RANGE);
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
        turn(MathUtils::random(-M_PI / 10, M_PI / 10));
      }
    }
    harvest();
    if (m_foodQuantity == MAX_FOOD_QUANTITY)
      flipDirection();
  }
  else
  {
    lookAt(m_anthill->getPosition());
    std::vector<Anthill *>
        visible = perceive<Anthill>();
    for (Anthill *anthill : visible)
    {
      if (anthill == m_anthill)
      {
        m_anthill->depositFood(m_foodQuantity);
        m_foodQuantity = 0.0f;
        break;
      }
    }
  }

  move();
}