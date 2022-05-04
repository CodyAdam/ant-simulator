#include <Pheromone.h>
#include <Renderer.h>
#include <Timer.h>

float const Pheromone::PHERO_RADIUS = 1.0f;

Pheromone::Pheromone(Environment *environment, const Vector2<float> &position, float strength)
    : Agent(environment, position, PHERO_RADIUS), m_strength(strength)
{
}

Pheromone::~Pheromone()
{
}

void Pheromone::addStrength(float amount)
{
  m_strength += amount;
}

float Pheromone::getStrength() const
{
  return m_strength;
}

void Pheromone::update()
{
  if (m_strength <= 0)
    setStatus(Status::destroy);
  else
    m_strength *= 0.99;
}
void Pheromone::draw() const
{
  float red = std::min(255.0f, std::max(0.5f * (m_strength - 300.0f), 0.0f));
  float blue = 255.0f - red;
  float green = std::max(0.0f, 160.0f - 0.7f * red);
  float alpha = std::min(255.0f, m_strength);
  Renderer::getInstance()
      ->drawCircle(getPosition(), getRadius(), Renderer::Color(red, green, blue, alpha));
}