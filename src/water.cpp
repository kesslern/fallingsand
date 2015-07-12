#include "water.h"
#include "game.h"
#include "particle.h"

#define MAX_DIST_MOVE 8

Water::Water(int idx)
{
  this->idx = idx;
  this->movable = true;
  this->liquid = true;
  this->r = 0;
  this->g = 0;
  this->b = 255;
}

void Water::move()
{
  int screenWidth = Particle::game->screenWidth;
  Particle** particles = Particle::game->particles;

  /* No bounds checking, watch out batman!!! */
  
  /* Check below us for empty space. */
  if (!particles[idx + screenWidth])
    {
      particles[idx + screenWidth] = particles[idx];
      particles[idx] = nullptr;
      this->idx += screenWidth;
    }
  /* Otherwise, if there is no particle  on either side, randomly flutter
   * to the left or right of that particle. */
  else if (!particles[idx + screenWidth - 1]
	   && !particles[idx + screenWidth + 1])
    {
      if (rand() % 2 == 1) {
	particles[idx + screenWidth + 1] = particles[idx];
	particles[idx] = nullptr;
	this->idx = idx + screenWidth + 1;
      } else {
	particles[idx + screenWidth - 1] = particles[idx];
	particles[idx] = nullptr;
	this->idx = idx + screenWidth - 1;
      }
    }
  /* Move left if possible (right isn't empty). */
  else if (!particles[idx + screenWidth - 1])
    {
      particles[idx + screenWidth - 1] = particles[idx];
      particles[idx] = nullptr;
      this->idx = idx + screenWidth -1;
    }
  /* Move right if possible (left isn't empty). */
  else if (!particles[idx + screenWidth + 1])
    {
      particles[idx + screenWidth + 1] = particles[idx];      
      particles[idx] = nullptr;
      this->idx = idx + screenWidth + 1;
    }
  else if (!particles[this->idx - screenWidth]) {

    int searchStart = this->idx + screenWidth;
    for (int xSearch = 1; xSearch < MAX_DIST_MOVE; xSearch++) {
      for (int ySearch = 0; ySearch < xSearch / 2; ySearch++) {
	int searchBase = searchStart + ySearch * screenWidth;
	if (!particles[searchBase + xSearch])
	  {
	    particles[searchBase + xSearch] = this;
	    particles[this->idx] = nullptr;
	    this->idx = searchBase + xSearch;
	  }
	else if (!particles[searchBase - xSearch])
	  {
	    particles[searchBase - xSearch] = this;
	    particles[this->idx] = nullptr;
	    this->idx = searchBase - xSearch;
	  }
      }
    }
     
  }
}

