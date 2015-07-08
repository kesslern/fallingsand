#include "water.h"
#include "game.h"
#include "particle.h"

Water::Water()
{
  this->movable = true;
  this->liquid = true;
  this->r = 0;
  this->g = 0;
  this->b = 255;
}

void Water::move(int i)
{
  int screenWidth = Particle::game->screenWidth;
  Particle** particles = Particle::game->particles;

  /* No bounds checking, watch out batman!!! */
  
  /* Check below us for empty space. */
  if (!particles[i + screenWidth])
    {
      particles[i + screenWidth] = particles[i];
      particles[i] = nullptr;
    }
  /* Otherwise, if there is no particle  on either side, randomly flutter
   * to the left or right of that particle. */
  else if (!particles[i + screenWidth - 1]
	   && !particles[i + screenWidth + 1])
    {
      if (rand() % 2 == 1) {
	particles[i + screenWidth + 1] = particles[i];
      } else {
	particles[i + screenWidth - 1] = particles[i];
      }
      particles[i] = nullptr;
    }
  /* Move left if possible (right isn't empty). */
  else if (!particles[i + screenWidth - 1])
    {
      particles[i + screenWidth - 1] = particles[i];
      particles[i] = nullptr;
    }
  /* Move right if possible (left isn't empty). */
  else if (!particles[i + screenWidth + 1])
    {
      particles[i + screenWidth + 1] = particles[i];      
      particles[i] = nullptr;
    }
}

  
