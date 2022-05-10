#include <Anthill.h>
#include <Renderer.h>
#include <AntBase.h>
#include <AntWithRules.h>
#include <SillyAnt.h>
#include <Ant.h>

Anthill::Anthill(Environment *env, const Vector2<float> initPos, int type)
    : Agent(env, initPos, 10.0f), m_foodQuantity(0.0f), m_totalFoodQuantity(0.0f), m_type(type)
{
}

Anthill::~Anthill()
{
  for (auto &ant : getEnvironment()->getAllInstancesOf<AntBase>())
  {
    if (ant->getAnthill() == this)
      ant->setStatus(Agent::Status::destroy);
  }
}

void Anthill::depositFood(float quantity)
{
  m_foodQuantity += quantity;
  m_totalFoodQuantity += quantity;
}

void Anthill::update()
{
  // create new ant base on the type if there is enough food
  if (m_foodQuantity >= 20.0f)
  {
    m_foodQuantity -= 20.0f;
    if (m_type == 0)
      new SillyAnt(this, getPosition());
    else if (m_type == 1)
      new Ant(this, getPosition());
    else if (m_type == 2)
      new AntWithRules(this, getPosition());
  }
}

void Anthill::draw() const
{
  Renderer *r = Renderer::getInstance();
  r->drawCircle(getPosition(), getRadius() + m_totalFoodQuantity / 100.0f, Renderer::Color(99, 220, 232, 255));
  r->drawString(getPosition() + Vector2<float>(-5, 20), "New ant : " + std::to_string((int)m_foodQuantity) + "/20", Renderer::Color(240, 240, 240, 255));
  r->drawString(getPosition() + Vector2<float>(-5, 30), "Total Food : " + std::to_string((int)m_totalFoodQuantity), Renderer::Color(240, 240, 240, 255));
}
