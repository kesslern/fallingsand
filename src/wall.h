#ifndef WALL_H
#define WALL_H

#include "particle.h"

class Wall : public Particle
{
 public:
  Wall(int idx);
  void move();
};

#endif
