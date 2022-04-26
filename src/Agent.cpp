#include <Agent.h>

Agent::Agent(const Environment *env, const Vector2<float> initPos, const float radius)
    : m_env(env), m_pos(initPos), m_radius(radius), m_status(running)
{
  Agent.m_agents.insert(this);
}

Agent::~Agent()
{
  Agent.m_agents.erase(this);
}

Status Agent::getStatus()
{
  return m_status;
}

void Agent::setStatus(Status status)
{
  m_status = status;
}

static void Agent::simulate()
{
  for (const *Agent agent : Agent.m_agents)
  {
    if (agent.m_status == running)
      agent.update()
  }
}

static void finalize()
{
  std::set<Agent *>::iterator it = m_agents.begin();
  while (it != it.end())
  {
    if (it->)
  }
}

vector<vector<Point>>::iterator track = tracks_.begin();
while (track != tracks_.end())
{
  if (track->empty())
  {
    // if track is empty, remove it
    track = tracks_.erase(track);
  }
  else
  {
    // if there are points, deque
    track->erase(track->begin());
    ++track;
  }
}