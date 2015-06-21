#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init(SDL_Window** window)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    return -1;

  *window = SDL_CreateWindow("SDL Demo",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH,
			    SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);

  if (*window == nullptr)
    return -2;
}
  

int main(int argc, char* args[])
{
  SDL_Window* window = nullptr;
  SDL_Surface* surface = nullptr;

  if (init(&window) < 0) {
    printf("Unable to init.");
    return -1;
  }

  surface = SDL_GetWindowSurface(window);

  SDL_LockSurface(surface);
  SDL_PixelFormat* fmt = surface->format;
  int x,y;
  for (y = 0; y < 50; y++) {
    for (x = 0; x < 50; x++) {
      Uint32* pixel = &((Uint32*)surface->pixels)[y * SCREEN_WIDTH + x];
      *pixel = *pixel | (fmt->Rmask & 0xFFFFFFFF);
    }
  }
  
  SDL_UnlockSurface(surface);
  SDL_UpdateWindowSurface(window);

  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
	quit = true;
      }
    }
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
  
