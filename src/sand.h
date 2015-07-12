#ifndef SAND_H
#define SAND_H

#include "particle.h"

class Sand : public Particle
{
public:
  Sand(int idx);
  void move();

private:
  bool canSwapWith(int idx);
  void swapOrMoveTo(int idx);
};

#endif
