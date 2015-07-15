#include <SDL2/SDL.h>
#include <random>
#include "game.h"
#include "wall.h"
#include "water.h"
#include "sand.h"
#include "particle.h"

Game::Game(int screen_width, int screen_height)
{
  this->screen_width_ = screen_width;
  this->screen_height_ = screen_height;
  
  /* Initialize SDL and get the renderer which we use to plot pixels.
   * Perform proper initializion checks too. */
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw -1;

  SDL_CreateWindowAndRenderer(screen_width_, screen_height_, 0, &window_, &renderer_);
  
  if (window_ == nullptr)
    throw -2;
  if (renderer_ == nullptr)
    throw -3;
  
  /* Allocate space for pointers to particle objects, one for each pixel on the screen. */
  size_t numParticles = static_cast<size_t>(screen_width_ * screen_height_);
  this->particles = static_cast<Particle**>(calloc(sizeof(Particle*),
						   numParticles));

  /* This reference needs to be initialized so particles have information needed to move. */
  Particle::game = this;
}

Game::~Game()
{
  /* Delete any particles in the pointer array. */
  for (int x = 0; x < screen_width_ * screen_height_; x++) {
    if (this->particles[x]) {
       delete(particles[x]);
     }
  }
  
  /* Free the pointer array and clean up SDL stuff. */
  free(this->particles);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::update()
{
  /* Delete the last line of particles */
  for (int x = 0; x < screen_width_; x++) {
    int idx = (screen_height_ - 1) * screen_width_ + x;
    if (this->particles[idx]) {
      delete(particles[idx]);
      particles[idx] = nullptr;
    }
  }

  /* Move paticles in each row except the bottom (since it's blank). */
  static bool loopDirectionToggle = false;

  /* Just loop backwards through the array of particles half of the time. */
  if (loopDirectionToggle)
    {
      for (int i = screen_width_ * (screen_height_ - 1); i >= 0; i--) {
	if (particles[i])
	  particles[i]->move();
      }
    }
  /* Otherwise, move right to left across each row from bottom to top. */
  else
    {
    for (int y = screen_height_ - 1; y >= 0; y--) {
      int offset = y * screen_width_;
      for (int x = 0; x < screen_width_; x++) {
	if (particles[offset + x])
	  particles[offset + x]->move();
	  
      }
    }
  }
  /* Swap directions on every other loop. */
  loopDirectionToggle = !loopDirectionToggle;
  
  /* Create some particles */
  int t = 0;
  while (t < screen_width_ - 50) { 
        t += rand() % 50 + 1;
	if (rand() % 2 == 1) 
	  particles[t] = new Water(t);
	else
	  particles[t] = new Sand(t);
  }

  /* Draw each particle on the screen. */
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  int i = 0; // so the offset doesn't have to be calculated on each loop
  for (int y = 0; y < screen_height_; y++) {
    for (int x = 0; x < screen_width_; x++) {
      if (particles[i]) {
	SDL_SetRenderDrawColor(renderer_,
			       particles[i]->r,
			       particles[i]->g,
			       particles[i]->b,
			       particles[i]->a);
	SDL_RenderDrawPoint(renderer_, x , y);
      }
      i++;
    }
  }

  SDL_RenderPresent(renderer_);
  SDL_Delay(1);
}

void Game::rightClick(int x, int y)
{
  for (int xi = x - 5; xi < x + 5; xi++) {
    for (int yi = y - 5; yi < y + 5; yi++) {
      if (xi > 0 && yi > 0 && xi < screen_width_ && yi < screen_height_) {
	int offset = yi * screen_width_ + xi;
	if (particles[offset]) {
	  delete particles[offset];
	  particles[offset] = nullptr;
	}
      }
    }
  }  
}

void Game::leftClick(int x, int y)
{
  for (int xi = x - 5; xi < x + 5; xi++) {
    for (int yi = y - 5; yi < y + 5; yi++) {
      if (xi > 0 && yi > 0 && xi < screen_width_ && yi < screen_height_) {
	int offset = yi * screen_width_ + xi;
	if (particles[offset]) {
	  delete particles[offset];
	}
	particles[offset] = new Wall(offset);
      }
    }
  }
}


void Game::calculateFps()
{
  static Uint32 startTime = SDL_GetTicks();
  static Uint32 lastFrameUpdate = current_frame_;
  
  Uint32 time = SDL_GetTicks();
  if (time - startTime > 3000)
    {
      printf("fps: %d\n", (current_frame_ - lastFrameUpdate) / 3);
      lastFrameUpdate = current_frame_;;
      startTime = time;
    }
}

void Game::processEvents()
{
  SDL_Event e;

  /* Keep track of mouse state. */
  static bool leftDown = false;
  static bool rightDown = false;

  /* Process each event. */
  while (SDL_PollEvent(&e) != 0) {
    
    if (e.type == SDL_QUIT)
      {
	this->quit_ = true;
      }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
      {
	Uint32 mask = SDL_GetMouseState(NULL, NULL);
	if (mask & SDL_BUTTON_LEFT) {
	  leftDown = true;
	} else if (mask & SDL_BUTTON_X1) {
	  rightDown = true;
	}
      }
    else if (e.type == SDL_MOUSEBUTTONUP)
      {
	/* Reset everything if a button comes up. */
	leftDown = false;
	rightDown = false;
      }
  }

  /* Process mouse events if either mouse button is down. */
  if (leftDown || rightDown)
    {
      int x, y;
      SDL_GetMouseState(&x, &y);
    
      if (leftDown)
	this->leftClick(x, y);
      if (rightDown)
	this->rightClick(x, y);
    }
}

bool Game::run()
{
  current_frame_++;
  this->processEvents();
  this->calculateFps();
  this->update();

  return !quit_;
}
