#include <AntBase.h>
#include <Timer.h>
#include <Renderer.h>

AntBase::AntBase(Environment *env, Anthill *anthill, const float speed)
    : Agent(env, anthill->getPosition(), 1.0f), m_speed(speed), m_anthill(anthill), m_lifeTime(1000.0f + rand() * 1500.0f), m_foodQuantity(0.0f), m_direction(Vector2<float>(1.0f, 0.0f).normalized())
{
}

AntBase::~AntBase()
{
}

void AntBase::lookAround()
{
}

void AntBase::lookAt(const Vector2<float> &target)
{
  m_direction = (target - getPosition()).normalized();
}

void AntBase::move()
{
  // You may notice that I don't use the deltaTime here because I implemented a Tick Per Second system which is more efficient.
  setPosition(getPosition() + m_direction * m_speed);
}

void AntBase::update()
{
  if (m_lifeTime > 0.0f)
  {
    m_lifeTime -= Timer::dt();
  }
  else
  {
    setStatus(Status::destroy);
  }
  lookAround();
  move();
}

void AntBase::draw() const
{
  if (m_foodQuantity > 0)
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(128, 255, 128, 255));
  else
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(255, 255, 255, 255));
}