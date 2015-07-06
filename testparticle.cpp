#include <stdio.h>
#include <SDL2/SDL.h>
#include "testparticle.h"

TestParticle::TestParticle(Uint8 r, Uint8 b, Uint8 g, bool movable)
{
  this->movable = movable;
  this->r = r;
  this->b = b;
  this->g = g;
}
