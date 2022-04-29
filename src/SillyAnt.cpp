#include <SillyAnt.h>
#include <Food.h>
#include <Timer.h>

SillyAnt::SillyAnt(Anthill *anthill)
    : AntBase(anthill->getEnvironment(), anthill)
{
}

SillyAnt::~SillyAnt()
{
}

void SillyAnt::update()
{
  if (m_lifeTime > 0.0f)
  {
    m_lifeTime -= Timer::dt();
  }
  else
  {
    setStatus(Status::destroy);
  }

  // look toward visible food if there is any
  std::vector<Food *> visible = perceive<Food>(m_direction, CONE_ANGLE, CONE_RANGE);
  if (visible.size() > 0)
  {
    lookAt(visible[0]->getPosition());
  }
  move();
}