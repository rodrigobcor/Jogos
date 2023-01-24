#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Colisão entre Objetos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 20);
    assert(fnt != NULL);
    SDL_Color clr = {0xFF,0x00,0x00,0xFF};
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt, " ", clr);
    assert(sfc != NULL);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(ren, sfc);
    assert(txt != NULL);

    /* EXECUÇÃO */
    SDL_Rect r = { 40, 10, 10,10 };
    SDL_Rect s = { 40, 40, 10,10 };
    SDL_Rect t = { 40, 70, 10,10 };
    SDL_Rect texto = { 10,50, 160,20 };
    char podio[3];
    int ordemPodio = 0;
    int goR = 1;
    int goS = 1;
    int goT = 1;
    int espera = 500;
    bool quit = false;
    while (!quit) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, txt, NULL, &texto);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderFillRect(ren, &s);
        SDL_RenderFillRect(ren, &t);
        SDL_RenderDrawLine(ren, 180, 0, 180, 100);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_KEYDOWN && goS) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        s.x -= 2;
                        break;
                    case SDLK_RIGHT:
                        s.x += 2;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                }
            } else if (evt.type == SDL_MOUSEMOTION && goT){
                t.x = evt.motion.x;
            }
        } else {
            espera = 500;
            if (goR) {
                r.x += 2;
            }
        }
        if (r.x + 10 > 180) {
            goR = 0;
            podio[ordemPodio] = 'r';
            ordemPodio++;
        }
        if (s.x + 10 > 180) {
            goS = 0;
            podio[ordemPodio] = 's';
            ordemPodio++;
        }
        if (t.x + 10 > 180) {
            goT = 0;
            podio[ordemPodio] = 't';
            ordemPodio++;
        }
        if (goR == 0 && goS == 0 && goT == 0){
            if (podio[0] == 'r'){
                sfc = TTF_RenderText_Blended(fnt, "Vitoria do triangulo 1", clr);
                txt = SDL_CreateTextureFromSurface(ren, sfc);
                SDL_RenderCopy(ren, txt, NULL, &texto);
            } else if (podio[0] == 's'){
                sfc = TTF_RenderText_Blended(fnt, "Vitoria do triangulo 2", clr);
                txt = SDL_CreateTextureFromSurface(ren, sfc);
                SDL_RenderCopy(ren, txt, NULL, &texto);
            } else if (podio[0] == 't'){
                sfc = TTF_RenderText_Blended(fnt, "Vitoria do triangulo 3", clr);
                txt = SDL_CreateTextureFromSurface(ren, sfc);
                SDL_RenderCopy(ren, txt, NULL, &texto);
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
