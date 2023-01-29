#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <deque>

enum direcao {
    PARADO,
    DOWN,
    UP,
    LEFT,
    RIGHT,
};

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow ("Snake", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 20);
    SDL_Color clr = {0,0,0,255};
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt, " ", clr);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, sfc);

    SDL_Event e;
    bool running = true;
    srand(time(0));

    std::deque<SDL_Rect> cobra;
    size_t size;
    size = 20;
    int dir = PARADO;
    SDL_Rect head = {250,250,10,10};
    SDL_Rect comida = {rand()%60*10,rand()%60*10,10,10};

    SDL_Rect caixaTexto = { 0,0, 150,50 };
    int espera = 50;
    bool pause = false;

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0,102,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255,128,0,255);
        std::for_each(cobra.begin(), cobra.end(), [&](auto& corpo_cobra)
        {
            SDL_RenderFillRect(renderer, &corpo_cobra);
        });
        SDL_RenderCopy(renderer, txt, NULL, &caixaTexto);
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderFillRect(renderer, &comida);
        SDL_RenderPresent(renderer);

        cobra.push_front(head);
        while(cobra.size() > size && dir != PARADO) {
            cobra.pop_back();
        }

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
                        if (dir == DOWN) {break;}
                        dir = UP;
                        break;
                    case SDLK_DOWN:
                        if (dir == UP) {break;}
                        dir = DOWN;
                        break;
                    case SDLK_LEFT:
                        if (dir == RIGHT) {break;}
                        dir = LEFT;
                        break;
                    case SDLK_RIGHT:
                        if (dir == LEFT) {break;}
                        dir = RIGHT;
                        break;
                    case SDLK_p:
                        dir = PARADO;
                        pause = !pause;
                        break;
                }
            }
        }

        espera = 50;
        if (!pause) {
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
        }

        if (pause){
            caixaTexto.x = 240;
            caixaTexto.y = 275;
            sfc = TTF_RenderText_Blended(fnt, "PAUSE", clr);
            txt = SDL_CreateTextureFromSurface(renderer, sfc);
            SDL_RenderCopy(renderer, txt, NULL, &caixaTexto);
        } else {
            sfc = TTF_RenderText_Blended(fnt, "", clr);
            txt = SDL_CreateTextureFromSurface(renderer, sfc);
            SDL_RenderCopy(renderer, txt, NULL, &caixaTexto);
        }

        if (head.x > 600) {head.x = 0;}
        if (head.x < 0) {head.x = 600;}
        if (head.y > 600) {head.y = 0;}
        if (head.y < 0) {head.y = 600;}

        //crescer e fazer outra comida
        if (head.x == comida.x && head.y == comida.y)
        {
            size += 1;
            comida = {rand()%60*10,rand()%60*10,10,10};
        }

        //colisao da cobra com o proprio corpo
        std::for_each(cobra.begin(), cobra.end(), [&](auto& corpo_cobra){
            if (head.x == corpo_cobra.x && head.y == corpo_cobra.y)
            {
                dir = PARADO;
            }
        });
    }

    return 0;
}
