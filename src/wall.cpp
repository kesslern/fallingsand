#include "wall.h"

Wall::Wall()
{
  this->movable = false;
  this->liquid = false;
  this->r = 220;
  this->g = 220;
  this->b = 220;
}

void Wall::move(int i)
{
  return;
}
