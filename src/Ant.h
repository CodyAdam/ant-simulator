#ifndef _ANT_H
#define _ANT_H

#include <AntBasePheromone.h>
#include <Vector2.h>

class Ant : public AntBasePheromone
{
private:
  /* data */
public:
  Ant(Anthill *anthill, Vector2<float> initPos);
  ~Ant();
  void update() override;
};

#endif