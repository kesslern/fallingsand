#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
class Game;

class Particle
{
public:
  virtual void move() = 0;
  static Game* game;
  virtual ~Particle();

  /* Location of the particle in the particles array in the game. */
  int idx;

  /* The last frame this particle was updated. */
  int lastUpdateFrame = 0;
  
  /* Particle properties. */
  bool movable;
  bool liquid;
  
  /* Color of the particle. */
  Uint8 r;
  Uint8 b;
  Uint8 g;
  Uint8 a = 255;
};

#endif
