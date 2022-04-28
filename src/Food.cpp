#include <Food.h>
#include <MathUtils.h>
#include <Renderer.h>

Food::Food(Environment *env, const Vector2<float> initPos, const float quantity)
    : Agent(env, initPos, MathUtils::circleRadius(quantity)), m_quantity(quantity)
{
}

Food::~Food()
{
}

float Food::getFoodQuantity() const
{
  return m_quantity;
}

float Food::collectFood(const float quantity)
{
  m_needRadiusUpdate = true;
  if (quantity > m_quantity)
  {
    float collected = m_quantity;
    m_quantity = 0;
    return collected;
  }
  else
  {
    m_quantity -= quantity;
    return quantity;
  }
}

void Food::update()
{
  if (m_quantity <= 0)
    setStatus(Status::destroy);

  if (m_needRadiusUpdate)
  {
    m_needRadiusUpdate = false;
    setRadius(MathUtils::circleRadius(m_quantity));
  }
  Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(154, 235, 38, 25));
}