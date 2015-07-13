#include <SDL2/SDL.h>
#include <random>
#include "game.h"
#include "wall.h"
#include "water.h"
#include "sand.h"
#include "particle.h"

Game::Game(int width, int height)
{
  /* Initialize SDL and get the renderer which we use to plot pixels.
   * Perform proper initializion checks too. */
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw -1;

  SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
  
  if (this->window == nullptr)
    throw -2;
  if (this->renderer == nullptr)
    throw -3;
  
  this->screenWidth = width;
  this->screenHeight = height;

  /* Allocate space for pointers to particle objects, one for each pixel on the screen. */
  this->particles = (Particle**) calloc(sizeof(Particle*),
				        (size_t) (this->screenWidth * this->screenHeight));

  /* This reference needs to be initialized so particles have information needed to move. */
  Particle::game = this;
}

Game::~Game()
{
  /* Delete any particles in the pointer array. */
  for (int x = 0; x < this->screenWidth * this->screenHeight; x++) {
    if (this->particles[x]) {
       delete(particles[x]);
     }
  }
  
  /* Free the pointer array and clean up SDL stuff. */
  free(this->particles);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::update()
{
  /* Delete the last line of particles */
  for (int x = 0; x < screenWidth; x++) {
    int idx = (screenHeight - 1) * screenWidth + x;
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
      for (int i = this->screenWidth * (this->screenHeight - 1); i >= 0; i--) {
	if (particles[i])
	  particles[i]->move();
      }
    }
  /* Otherwise, move right to left across each row from bottom to top. */
  else
    {
    for (int y = screenHeight - 1; y >= 0; y--) {
      int offset = y * screenWidth;
      for (int x = 0; x < screenWidth; x++) {
	if (particles[offset + x])
	  particles[offset + x]->move();
	  
      }
    }
  }
  /* Swap directions on every other loop. */
  loopDirectionToggle = !loopDirectionToggle;
  
  /* Create some particles */
  int t = 0;
  while (t < this->screenWidth - 50) { 
        t += rand() % 50 + 1;
	if (rand() % 2 == 1) 
	  particles[t] = new Water(t);
	else
	  particles[t] = new Sand(t);
  }

  /* Draw each particle on the screen. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  int i = 0; // so the offset doesn't have to be calculated on each loop
  for (int y = 0; y < this->screenHeight; y++) {
    for (int x = 0; x < this->screenWidth; x++) {
      if (this->particles[i]) {
	SDL_SetRenderDrawColor(renderer,
			       particles[i]->r,
			       particles[i]->g,
			       particles[i]->b,
			       particles[i]->a);
	SDL_RenderDrawPoint(this->renderer, x , y);
      }
      i++;
    }
  }

  SDL_RenderPresent(renderer);
  SDL_Delay(1);
}

void Game::rightClick(int x, int y)
{
  for (int xi = x - 5; xi < x + 5; xi++) {
    for (int yi = y - 5; yi < y + 5; yi++) {
      if (xi > 0 && yi > 0 && xi < this->screenWidth && yi < this->screenHeight) {
	int offset = yi * this->screenWidth + xi;
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
      if (xi > 0 && yi > 0 && xi < this->screenWidth && yi < this->screenHeight) {
	int offset = yi * this->screenWidth + xi;
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
  static int lastFrameUpdate = this->currentFrame;
  
  Uint32 time = SDL_GetTicks();
  if (time - startTime > 3000)
    {
      printf("fps: %d\n", (this->currentFrame - lastFrameUpdate) / 3);
      lastFrameUpdate = this->currentFrame;;
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
	this->quit = true;
      }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
      {
	int mask = SDL_GetMouseState(NULL, NULL);
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
  this->currentFrame++;
  this->processEvents();
  this->calculateFps();
  this->update();

  return !this->quit;
}
