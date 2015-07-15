#include "game.h"
#include "sand.h"

Sand::Sand(int idx)
{
  this->array_index_ = idx;
  this->movable = true;
  this->liquid = false;
  this->r = 237;
  this->g = 201;
  this->b = 175;
  this->lastUpdateFrame = Particle::game->current_frame_;
}

void Sand::move()
{
  if (this->lastUpdateFrame == Particle::game->current_frame_)
    return;

  this->lastUpdateFrame = Particle::game->current_frame_;
  int screenWidth = Particle::game->screen_width_;

  /* No bounds checking, watch out batman!!! */
  
  /* Check below us for empty space. */
  if (canSwapWith(array_index_ + screenWidth))
    {
      swapOrMoveTo(array_index_ + screenWidth);
    }
  /* Otherwise, if there is no particle  on either side, randomly flutter
   * to the left or right of that particle. */
  else if (canSwapWith(array_index_ + screenWidth - 1)
	   && canSwapWith(array_index_ + screenWidth + 1))
    {
      if (rand() % 2 == 1) {
        swapOrMoveTo(array_index_ + screenWidth);
      } else {
        swapOrMoveTo(array_index_ + screenWidth - 1);
      }
    }
  /* Move left if possible (right isn't empty). */
  else if (canSwapWith(array_index_ + screenWidth - 1))
    {
      swapOrMoveTo(array_index_ + screenWidth - 1);
    }
  /* Move right if possible (left isn't empty). */
  else if (canSwapWith(array_index_ + screenWidth + 1))
    {
      swapOrMoveTo(array_index_ + screenWidth + 1);
    }
}

bool Sand::canSwapWith(int idx)
{
  Particle* p = Particle::game->particles[idx];
  return !p || p->liquid;
}

void Sand::swapOrMoveTo(int newIndex)
{
  /* Backup the old particle*/
  Particle* oldParticle = Particle::game->particles[newIndex];
  Particle::game->particles[newIndex] = this;
  Particle::game->particles[this->array_index_] = oldParticle;;
  if (oldParticle)
    oldParticle->array_index_ = this->array_index_;
  this->array_index_ = newIndex;
}
