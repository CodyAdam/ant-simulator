#ifndef _SILLYANT_H_
#define _SILLYANT_H_

#include <AntBase.h>

class SillyAnt : public AntBase
{
private:
  /* data */
public:
  SillyAnt(Anthill *anthill, Vector2<float> initPos);
  ~SillyAnt();
  void update() override;
};

#endif