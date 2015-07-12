#include <SDL2/SDL.h>
#include <stdio.h>
#include <random>
#include "game.h"

int main()
{
  srand(time(NULL));
  Game game(800, 600);

  int frames = 0;
  Uint32 startTime = SDL_GetTicks();
  
  while (game.run())
    {
      Uint32 time = SDL_GetTicks();

      /* Update FPS every 3 seconds. */
      if (time - startTime > 3000)
	{
	  int fps = frames / 3;
	  printf("fps: %d\n", fps);
	  frames = 0;
	  startTime = time;
	}
      
      frames++;
    }
  
  return 0;
}
