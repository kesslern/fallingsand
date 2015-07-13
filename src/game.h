#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
class Particle;

class Game
{
public:
  Game(int screenWidth, int screenHeight);
  ~Game();
  bool run();

  int screenWidth;
  int screenHeight;
  int currentFrame = 0;
  Particle** particles;

private:
  /* Create walls. */
  void leftClick(int x, int y);
  /* Delete particles. */
  void rightClick(int x, int y);
  /* Calculate the FPS at some given interval. */
  void calculateFps();
  /* Process mouse buttons and key presses. */
  void processEvents();
  /* Update all the particles on the screen. */
  void update();
  
  SDL_Window* window;
  SDL_Renderer* renderer;
  Uint32 fps;
  bool quit = false;
};

#endif
