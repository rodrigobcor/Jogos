#include <stdio.h>

#include "SDL2_gfxPrimitives.h"

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char* argv[])
{

   if (SDL_Init(SDL_INIT_VIDEO))
   {
      printf ("SDL_Init Error: %s", SDL_GetError());
      return 1;
   }

   SDL_Window *window = SDL_CreateWindow("SDL2_gfx test", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
   if (window == NULL)
   {
      printf ("SDL_CreateWindow Error: %s", SDL_GetError());
      SDL_Quit();
      return 2;
   }

   SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (renderer == NULL)
   {
      SDL_DestroyWindow(window);
      printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
      SDL_Quit();
      return 3;
   }

   SDL_Event e;

   int quit = 0;
   while (!quit)
   {
      if (SDL_PollEvent(&e))
      {
         if (e.type == SDL_QUIT)
            quit = 1;
      }
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(renderer);

    //tive que fazer varias linhas pq o for loop trava o renderer
      aalineRGBA(renderer, 0, HEIGHT / 3, WIDTH, HEIGHT / 3 * 2, 0, 0, 0, 255);
      aalineRGBA(renderer, 0, HEIGHT / 6, WIDTH, HEIGHT / 6 * 5, 0, 0, 0, 255);
      aalineRGBA(renderer, 0, HEIGHT / 6 * 5, WIDTH, HEIGHT / 6, 0, 0, 0, 255);
      aalineRGBA(renderer, 0, HEIGHT / 3 * 2, WIDTH, HEIGHT / 3, 0, 0, 0, 255);
      aalineRGBA(renderer, 0            , 0, WIDTH        , HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 8    , 0, WIDTH / 8 * 7, HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 4    , 0, WIDTH / 4 * 3, HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 8 * 3, 0, WIDTH / 8 * 5, HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 2    , 0, WIDTH / 2    , HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 8 * 5, 0, WIDTH / 8 * 3, HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 4 * 3, 0, WIDTH / 4    , HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH / 8 * 7, 0, WIDTH / 8    , HEIGHT, 0, 0, 0, 255);
      aalineRGBA(renderer, WIDTH        , 0, 0            , HEIGHT, 0, 0, 0, 255);


      thickLineRGBA(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2, 5, 0, 0, 0, 160);
      boxRGBA(renderer, WIDTH / 8, HEIGHT / 6, WIDTH / 4, HEIGHT / 3, 255, 0, 0, 255);
      filledCircleRGBA(renderer, WIDTH / 4 * 3 + 40, HEIGHT / 4, 40, 0, 255, 0, 255);
      filledPieRGBA(renderer, WIDTH / 8 + 40, HEIGHT / 3 * 2 + 40, 40, 45, 315, 0, 0, 255, 255);
      filledTrigonRGBA(renderer, WIDTH / 4 * 3, HEIGHT / 3 * 2, WIDTH / 4 * 3 + 40, HEIGHT / 3 * 2 + 80, WIDTH / 4 * 3 + 80, HEIGHT / 3 * 2, 120, 120, 120, 255);

      SDL_RenderPresent(renderer);
      SDL_Delay(10);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0;
}
