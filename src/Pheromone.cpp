#include <Pheromone.h>
#include <Renderer.h>

Pheromone::Pheromone(Environment *environment, const Vector2<float> &position, float strength)
    : Agent(environment, position, 2.0f), m_strength(strength)
{
}

Pheromone::~Pheromone()
{
}

float Pheromone::DECAY_PER_TICK = 0.01;

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
    m_strength -= DECAY_PER_TICK;
}
void Pheromone::draw() const
{
  Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(0, 150, 150, std::min(255.0f, m_strength)));
}