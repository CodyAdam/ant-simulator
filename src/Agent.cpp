#include <Agent.h>

Agent::Agent(Environment *env, const Vector2<float> initPos, const float radius)
    : LocalizedEntity(env, initPos, radius), m_status(Status::running)
{
  agents.insert(this);
}

Agent::~Agent()
{
  agents.erase(this);
}

Agent::Status Agent::getStatus() const
{
  return m_status;
}

void Agent::setStatus(Status status)
{
  m_status = status;
}

void Agent::simulate()
{
  std::set<Agent *>::iterator it = agents.begin();
  while (it != agents.end())
  {
    if ((*it)->m_status == Status::running)
    {
      (*it)->update();
      it++;
    }
    else
      it = agents.erase(it);
  }
  finalize();
}

void Agent::finalize()
{
  std::set<Agent *>::iterator it = agents.begin();
  while (it != agents.end())
  {
    if ((*it)->m_status == Status::destroy)
      it = agents.erase(it);
    else
      it++;
  }
}
