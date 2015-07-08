#ifndef WALL_H
#define WALL_H

#include "particle.h"

class Wall : public Particle
{
 public:
  Wall();
  void move(int i);
};

#endif
