#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>

class Particle
{
public:
  Uint8 r;
  Uint8 b;
  Uint8 g;
  Uint8 a = 255;
  bool movable = true;
};

#endif
