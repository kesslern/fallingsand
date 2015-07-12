#include "game.h"
#include "sand.h"

Sand::Sand(int idx)
{
  this->idx = idx;
  this->movable = true;
  this->liquid = false;
  this->r = 237;
  this->g = 201;
  this->b = 175;
}

void Sand::move()
{
  int screenWidth = Particle::game->screenWidth;

  /* No bounds checking, watch out batman!!! */
  
  /* Check below us for empty space. */
  if (canSwapWith(idx + screenWidth))
    {
      swapOrMoveTo(idx + screenWidth);
    }
  /* Otherwise, if there is no particle  on either side, randomly flutter
   * to the left or right of that particle. */
  else if (canSwapWith(idx + screenWidth - 1)
	   && canSwapWith(idx + screenWidth + 1))
    {
      if (rand() % 2 == 1) {
        swapOrMoveTo(idx + screenWidth);
      } else {
        swapOrMoveTo(idx + screenWidth - 1);
      }
    }
  /* Move left if possible (right isn't empty). */
  else if (canSwapWith(idx + screenWidth - 1))
    {
      swapOrMoveTo(idx + screenWidth - 1);
    }
  /* Move right if possible (left isn't empty). */
  else if (canSwapWith(idx + screenWidth + 1))
    {
      swapOrMoveTo(idx + screenWidth + 1);
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
  Particle::game->particles[this->idx] = oldParticle;;
  if (oldParticle)
    oldParticle->idx = this->idx;
  this->idx = newIndex;
}
