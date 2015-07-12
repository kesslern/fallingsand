#ifndef WATER_H
#define WATER_H

#include "particle.h"

class Water : public Particle
{
public:
  Water(int idx);
  void move();

private:
  bool searchAndMoveDownLeft();
  bool searchAndMoveDownRight();
};

#endif
