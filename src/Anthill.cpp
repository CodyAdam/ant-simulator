#include <Anthill.h>
#include <Renderer.h>

Anthill::Anthill(Environment *env, const Vector2<float> initPos)
    : Agent(env, initPos, 10.0f), m_foodQuantity(0.0f)
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

void Anthill::draw() const
{
  Renderer *r = Renderer::getInstance();
  r->drawCircle(getPosition(), getRadius(), Renderer::Color(99, 220, 232, 255));
  r->drawString(getPosition() + Vector2<float>(-5, 20), "Food : " + std::to_string((int)m_foodQuantity), Renderer::Color(240, 240, 240, 255));
}
