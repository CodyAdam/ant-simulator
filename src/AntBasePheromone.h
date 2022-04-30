#ifndef _ANTBASEPHEROMONE_H
#define _ANTBASEPHEROMONE_H

#include <AntBase.h>
#include <Pheromone.h>

class AntBasePheromone : public AntBase
{
private:
  static float PHERO_EXTENT;

public:
  AntBasePheromone(Anthill *anthill, Vector2<float> initPos, float speed = 1);
  ~AntBasePheromone();
  void putPheromone(float q);
  Pheromone *choosePheromone() const;
};

#endif
