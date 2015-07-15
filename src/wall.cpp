#include "wall.h"
#include "game.h"

Wall::Wall(int idx)
{
  this->array_index_ = idx;
  this->movable = false;
  this->liquid = false;
  this->r = 220;
  this->g = 220;
  this->b = 220;
}

void Wall::move()
{
  this->lastUpdateFrame = Particle::game->current_frame_;
  return;
}
