#ifndef _AGENT_H
#define _AGENT_H

#include <Environment.h>

class Agent : public Environment::LocalizedEntity
{
public:
  typedef enum
  {
    running,
    destroy
  } Status;

private:
  Status m_status;
  inline static std::set<Agent *> s_agents = std::set<Agent *>();

public:
  Agent(Environment *env, const Vector2<float> initPos, const float radius = Environment::LocalizedEntity::defaultRadius());
  ~Agent();
  virtual void update() = 0;
  virtual void draw() const = 0;
  Status getStatus() const;
  void setStatus(Status status);
  static void simulate();
  static void render();
  static void finalize();
};

#endif