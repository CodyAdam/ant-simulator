#ifndef _AGENT_H
#define _AGENT_H

#include <Environment.h>

class Agent : private Environment::LocalizedEntity
{
private:
  Evironment *m_env;
  Vector2<float> m_pos;
  float m_radius;
  Status m_status;

  static std::set<Agent*> m_agents;

  typedef enum { running, destroy } Status;
public:
  Agent(const Environment *env, const Vector2<float> initPos, const float radius = Environment::LocalizedEntity::defaultRadius());
  ~Agent();
  virtual void update(); 
  Status getStatus();
  void setStatus(Status status);
  static void simulate();
  static void finalize();
};

#endif