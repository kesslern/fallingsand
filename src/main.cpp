#include <SDL2/SDL.h>
#include <stdio.h>
#include <random>
#include "game.h"

int main()
{
  srand(time(NULL));
  Game game(800, 600);

  while (game.run())

    return 0;
}
