#include <Agent.h>
#include <iostream>

Agent::Agent(Environment *env, const Vector2<float> initPos, const float radius)
    : LocalizedEntity(env, initPos, radius), m_status(Status::running)
{
  s_agents.insert(this);
}

Agent::~Agent()
{
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

  auto it = s_agents.begin();
  while (it != s_agents.end())
  {
    Agent *agent = *it;
    if (agent->getStatus() == running)
    {
      agent->update();
      it++;
    }
    else
    {
      it = s_agents.erase(it);
      delete agent;
    }
  }
}

void Agent::render()
{
  for (auto agent : s_agents)
    if (agent->getStatus() == running)
      agent->draw();
}

void Agent::finalize()
{
  for (auto agent : s_agents)
    delete agent;
  s_agents.clear();
}
