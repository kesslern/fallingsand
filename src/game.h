#ifndef GAME_H
#define GAME_H

class Particle;
class SDL_Window;
class SDL_Renderer;

class Game
{
public:
  Game(int screen_width, int screen_height);
  ~Game();
  bool run();

  int screen_width_;
  int screen_height_;
  unsigned int current_frame_ = 0;
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
  
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  int fps_;
  bool quit_ = false;
};

#endif
