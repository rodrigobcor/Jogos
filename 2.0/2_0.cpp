#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
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
    SDL_Rect r = { 100, 20, 30,30 };
    SDL_Rect texto = { 10,10, 60,15 };
    SDL_Event evt;
    bool quit = false;
    SDL_Point clickOffset;
    SDL_Rect * selectedRect = NULL;
    int xOriginal, yOriginal;

    SDL_Point mousePos;

    while (!quit) {
        SDL_PollEvent(&evt);
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, txt, NULL, &texto);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        switch (evt.type) {
            case SDL_KEYDOWN:
                if (evt.key.keysym.sym == SDLK_ESCAPE) {
                    selectedRect = NULL;
                    sfc = TTF_RenderText_Blended(fnt, "Parado", clr);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_RenderCopy(ren, txt, NULL, &texto);
                    r.x = xOriginal;
                    r.y = yOriginal;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (evt.button.button == SDL_BUTTON_LEFT)
                {
                    sfc = TTF_RenderText_Blended(fnt, "Parado", clr);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_RenderCopy(ren, txt, NULL, &texto);
                    selectedRect = NULL;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (evt.button.button == SDL_BUTTON_LEFT)
                {
                    xOriginal = r.x;
                    yOriginal = r.y;
                    if (SDL_PointInRect(&mousePos, &r))
                    {
                        selectedRect = &r;
                        sfc = TTF_RenderText_Blended(fnt, "Clicado", clr);
                        txt = SDL_CreateTextureFromSurface(ren, sfc);
                        SDL_RenderCopy(ren, txt, NULL, &texto);
                        clickOffset.x = mousePos.x - r.x;
                        clickOffset.y = mousePos.y - r.y;
                        break;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                mousePos = { evt.motion.x, evt.motion.y };
                if (selectedRect != NULL)
                {
                    sfc = TTF_RenderText_Blended(fnt, "Movendo", clr);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_RenderCopy(ren, txt, NULL, &texto);
                    selectedRect->y = mousePos.y - clickOffset.y;
                    selectedRect->x = mousePos.x - clickOffset.x;
                }
                break;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
