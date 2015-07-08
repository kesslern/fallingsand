#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
class Particle;

class Game
{
public:
  Game(int screenWidth, int screenHeight);
  ~Game();
  void update();
  void flutter(int i);
  bool run();

  int screenWidth;
  int screenHeight;
  Particle** particles;
 
private:
  /* Create walls. */
  void leftClick(int x, int y);
  /* Delete particles. */
  void rightClick(int x, int y);
   SDL_Window* window;
  SDL_Renderer* renderer;
};

#endif
