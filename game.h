#ifndef GAME_H
#define GAME_H

#include "particle.h"

class Game
{
public:
  Game(int screenWidth, int screenHeight);
  ~Game();
  void update();
  void flutter(int i);
  bool run();
  
private:
  void deletetmp(int x, int y);
  bool mouseDown = false;
  int screenWidth;
  int screenHeight;
  SDL_Window* window;
  Particle** particles;
  SDL_Renderer* renderer;
};

#endif
