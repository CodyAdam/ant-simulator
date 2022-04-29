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
  // You may notice that I didn't use the deltaTime here because I implemented a Tick Per Second system which is more efficient.
  translate(m_direction * m_speed);
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
  std::vector<Food *> foodsOnAnt = perceive<Food>();
  for (Food *food : foodsOnAnt)
  {
    // collect as much food as possible from the food on the ant
    float freeSpace = MAX_FOOD_QUANTITY - m_foodQuantity;
    m_foodQuantity += food->collectFood(freeSpace);
  }
  return quantity;
}

void AntBase::draw() const
{
  if (m_foodQuantity > 0)
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(128, 255, 128, 255));
  else
    Renderer::getInstance()->drawPixel(getPosition(), Renderer::Color(255, 255, 255, 255));
}