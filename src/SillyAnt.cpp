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
    m_lifeTime -= Timer::dt();
  else
    setStatus(Status::destroy);

  // Turn randomly if not full
  if (m_foodQuantity < MAX_FOOD_QUANTITY)
  {
    turn(MathUtils::random(-M_PI / 10, M_PI / 10));
  }
  else
  {
    lookAt(m_anthill->getPosition());
  }

  // look toward visible food if there is any
  std::vector<Food *>
      visible = perceive<Food>(m_direction, CONE_ANGLE, CONE_RANGE);
  if (visible.size() > 0)
  {
    lookAt(visible[0]->getPosition());
  }
  harvest();

  move();
}