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
  /* If we're above a body of water, absorb into it. */
  else if (!particles[idx - screenWidth]
	   && particles[idx + screenWidth]
	   && particles[idx + screenWidth]->liquid)
    {
      if (searchAndMoveDownLeft()) {}
      else {searchAndMoveDownRight();}
    }
}

bool Water::searchAndMoveDownLeft()
{
  int screenWidth = Particle::game->screenWidth;
  Particle** particles = Particle::game->particles;
  
  /* Search until the end of the screen until we run out of liquid
   * to absorb into or we find an empty place to go. */
  for (int searchX = 1;
       searchX <= idx % screenWidth && searchX <= MAX_DIST_MOVE;
       searchX++) 
    {
      if (!particles[idx + screenWidth - searchX])
	{
	 particles[idx + screenWidth - searchX] = this;
	 particles[idx] = nullptr;
	  this->idx = idx + screenWidth - searchX;
	  return true;
	}
      /* Check another row down too... it happens. */
      else if (!particles[idx + screenWidth * 2 - searchX])
	{
	  particles[idx + screenWidth * 2 - searchX] = this;
	  particles[idx] = nullptr;
	  this->idx = idx + screenWidth * 2 - searchX;
	  return true;
	}
      // Stop searching if it's the end of the liquid pool
      else if (particles[idx + screenWidth - searchX]
	       && !particles[idx + screenWidth - searchX]->liquid)
	{
	  break;
	}
    }
  
  return false;
}

bool Water::searchAndMoveDownRight()
{
  const int screenWidth = Particle::game->screenWidth;
  Particle** particles = Particle::game->particles;
  
  /* Search until the end of the screen until we run out of liquid
   * to absorb into or we find an empty place to go. */
  for (int searchX = 1;
       searchX <= screenWidth - idx % screenWidth && searchX <= MAX_DIST_MOVE;
       searchX++) 
    {
      if (!particles[idx + screenWidth + searchX])
	{
	 particles[idx + screenWidth + searchX] = this;
	 particles[idx] = nullptr;
	  this->idx = idx + screenWidth + searchX;
	  return true;
	}
      /* Check another row down too... it happens. */
      else if (!particles[idx + screenWidth * 2 + searchX])
	{
	 particles[idx + screenWidth * 2 + searchX] = this;
	 particles[idx] = nullptr;
	  this->idx = idx + screenWidth * 2 + searchX;
	  return true;
	}
      // Stop searching if it's the end of the liquid pool
      else if (particles[idx + screenWidth + searchX]
	       && !particles[idx + screenWidth + searchX]->liquid)
	{
	  break;
	}
    }
  
  return false;

}
