#include <SillyAnt.h>
#include <Food.h>
#include <Timer.h>

SillyAnt::SillyAnt(Anthill *anthill, Vector2<float> initPos)
    : AntBase(anthill, initPos)
{
}

SillyAnt::~SillyAnt()
{
}

void SillyAnt::update()
{
  if (m_lifeTime > 0.0f)
    m_lifeTime -= 1;
  else
    setStatus(Status::destroy);

  // Turn randomly if not full
  if (m_foodQuantity < MAX_FOOD_QUANTITY)
  {
    turn(MathUtils::random(-M_PI / 30, M_PI / 30));
  }
  else
  {
    lookAt(m_anthill->getPosition());
    std::vector<Anthill *>
        ah = perceive<Anthill>();
    for (Anthill *anthill : ah)
    {
      if (anthill == m_anthill)
      {
        anthill->depositFood(m_foodQuantity);
        m_foodQuantity = 0;
        flipDirection();

        break;
      }
    }
  }

  // look toward visible food if there is any
  std::vector<Food *>
      visible = perceive<Food>(m_direction, FOOD_ANGLE, FOOD_EXTENT, FOOD_MIN_EXTENT);
  if (visible.size() > 0)
  {
    lookAt(visible[0]->getPosition());
  }
  harvest();

  move();
}