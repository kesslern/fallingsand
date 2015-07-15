#include "water.h"
#include "game.h"
#include "particle.h"

#define MAX_DIST_MOVE 8

Water::Water(int idx)
{
  this->array_index_ = idx;
  this->movable = true;
  this->liquid = true;
  this->r = 0;
  this->g = 0;
  this->b = 255;
  this->lastUpdateFrame = Particle::game->current_frame_;
}

void Water::move()
{
  if (this->lastUpdateFrame == Particle::game->current_frame_)
    return;

  this->lastUpdateFrame = Particle::game->current_frame_;
  int screenWidth = Particle::game->screen_width_;
  Particle** particles = Particle::game->particles;

  /* No bounds checking, watch out batman!!! */
  
  /* Check below us for empty space. */
  if (!particles[array_index_ + screenWidth])
    {
      particles[array_index_ + screenWidth] = particles[array_index_];
      particles[array_index_] = nullptr;
      this->array_index_ += screenWidth;
    }
  /* Otherwise, if there is no particle  on either side, randomly flutter
   * to the left or right of that particle. */
  else if (!particles[array_index_ + screenWidth - 1]
	   && !particles[array_index_ + screenWidth + 1])
    {
      if (rand() % 2 == 1) {
	particles[array_index_ + screenWidth + 1] = particles[array_index_];
	particles[array_index_] = nullptr;
	this->array_index_ = array_index_ + screenWidth + 1;
      } else {
	particles[array_index_ + screenWidth - 1] = particles[array_index_];
	particles[array_index_] = nullptr;
	this->array_index_ = array_index_ + screenWidth - 1;
      }
    }
  /* Move left if possible (right isn't empty). */
  else if (!particles[array_index_ + screenWidth - 1])
    {
      particles[array_index_ + screenWidth - 1] = particles[array_index_];
      particles[array_index_] = nullptr;
      this->array_index_ = array_index_ + screenWidth -1;
    }
  /* Move right if possible (left isn't empty). */
  else if (!particles[array_index_ + screenWidth + 1])
    {
      particles[array_index_ + screenWidth + 1] = particles[array_index_];      
      particles[array_index_] = nullptr;
      this->array_index_ = array_index_ + screenWidth + 1;
    }
  else if (!particles[this->array_index_ - screenWidth]) {

    int searchStart = this->array_index_ + screenWidth;
    for (int xSearch = 1; xSearch < MAX_DIST_MOVE; xSearch++) {
      for (int ySearch = 0; ySearch < xSearch / 2; ySearch++) {
	int searchBase = searchStart + ySearch * screenWidth;
	if (!particles[searchBase + xSearch])
	  {
	    particles[searchBase + xSearch] = this;
	    particles[this->array_index_] = nullptr;
	    this->array_index_ = searchBase + xSearch;
	  }
	else if (!particles[searchBase - xSearch])
	  {
	    particles[searchBase - xSearch] = this;
	    particles[this->array_index_] = nullptr;
	    this->array_index_ = searchBase - xSearch;
	  }
      }
    }
  }
}

