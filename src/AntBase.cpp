#include <AntBase.h>
#include <Timer.h>
#include <Renderer.h>
#include <Food.h>

AntBase::AntBase(Environment *env, Anthill *anthill, const float speed)
    : Agent(env, anthill->getPosition(), 1.0f), m_speed(speed), m_direction(Vector2<float>(1.0f, 0.0f).normalized()), m_lifeTime(1000.0f + rand() * 1500.0f), m_foodQuantity(0.0f), m_anthill(anthill)
{
}

AntBase::~AntBase() {}

float AntBase::MAX_FOOD_QUANTITY = 5.0f;
float AntBase::CONE_ANGLE = M_PI / 2.0f;
float AntBase::CONE_RANGE = 3.0f;

void AntBase::lookAt(const Vector2<float> &target)
{
  m_direction = (target - getPosition()).normalized();
}

void AntBase::move()
{
  // You may notice that I don't use the deltaTime here because I implemented a Tick Per Second system which is more efficient.
  setPosition(getPosition() + m_direction * m_speed);
}

void AntBase::turn(float angle)
{
  m_direction = m_direction.rotate(angle);
}

void AntBase::flipDirection()
{
  m_direction = m_direction.rotate(M_PI);
}

void AntBase::dropFood(float quantity)
{
  if (m_foodQuantity - quantity >= 0.0f)
  {
    new Food(getEnvironment(), getPosition(), quantity);
    m_foodQuantity -= quantity;
  }
  else
  {
    new Food(getEnvironment(), getPosition(), m_foodQuantity);
    m_foodQuantity = 0.0f;
  }
}

float AntBase::harvest()
{
  float quantity = 0.0f;
  // for (auto &food : getEnvironment()->getFoods())
  // {
  //   if (food->getPosition().distance(getPosition()) < 3.0f)
  //   {
  //     quantity += food->getQuantity();
  //     food->die();
  //   }
  // }
  return quantity;
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
  // look toward visible food if there is any
  std::vector<Food *> visible = getVisible<Food>();
  if (visible.size() > 0)
  {
    lookAt(visible[0]->getPosition());
  }
  move();
}

void AntBase::draw() const
{
  if (m_foodQuantity > 0)
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(128, 255, 128, 255));
  else
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(255, 255, 255, 255));
}