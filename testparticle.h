#ifndef TEST_PARTICLE_H
#define TEST_PARTICLE_H

#include "particle.h"
#include <SDL2/SDL.h>

class TestParticle : public Particle
{
 public:
  TestParticle(Uint8 r, Uint8 b, Uint8 g, bool movable);
};

#endif
