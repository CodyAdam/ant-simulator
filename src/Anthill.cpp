#include <Anthill.h>
#include <Renderer.h>

Anthill::Anthill(Environment *env, const Vector2<float> initPos)
    : Agent(env, initPos, 10.0f)
{
}

Anthill::~Anthill()
{
}

void Anthill::depositFood(float quantity)
{
  m_foodQuantity += quantity;
}

void Anthill::update()
{
}

float Anthill::getFoodQuantity() const
{
  return m_foodQuantity;
}

void Anthill::draw() const
{
  Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(99, 220, 232, 255));
}
