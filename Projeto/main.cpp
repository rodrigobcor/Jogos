#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <deque>

enum direcao {
    PARADO,
    DOWN,
    UP,
    LEFT,
    RIGHT
};

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow ("Snake", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;
    bool running = true;

    std::deque<SDL_Rect> cobra;
    size_t size = 1;
    int dir = PARADO;
    SDL_Rect head {250,250,10,10};
    SDL_Rect comida {rand()%100-3,rand()%100-6,10,10};
    int espera = 50;

    while (running)
    {
        size = 5;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&e, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (e.type == SDL_QUIT) {running = false;}
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_UP:
                        dir = UP;
                        break;
                    case SDLK_DOWN:
                        dir = DOWN;
                        break;
                    case SDLK_LEFT:
                        dir = LEFT;
                        break;
                    case SDLK_RIGHT:
                        dir = RIGHT;
                        break;
                }
            }
        }

        espera = 50;
        switch(dir)
        {
            case DOWN:
                head.y += 10;
                break;
            case UP:
                head.y -= 10;
                break;
            case LEFT:
                head.x -= 10;
                break;
            case RIGHT:
                head.x += 10;
                break;
        }

        std::for_each(cobra.begin(), cobra.end(), [&](auto& corpo_cobra)
        {
            if (head.x == corpo_cobra.x && head.y == corpo_cobra.y)
            {
                size = 1;
            }
        });

        cobra.push_front(head);
        while(cobra.size() > size) {
            cobra.pop_back();
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        std::for_each(cobra.begin(), cobra.end(), [&](auto& corpo_cobra)
        {
            SDL_RenderFillRect(renderer, &corpo_cobra);
        });
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderFillRect(renderer, &comida);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
