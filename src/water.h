#ifndef WATER_H
#define WATER_H

#include "particle.h"

class Water : public Particle
{
 public:
  Water();
  void move(int i);
};

#endif
