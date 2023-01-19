#include <SDL2/SDL.h>

//struct line{
//    int x1, y1, x2, y2;
//};

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        200, 100, SDL_WINDOW_SHOWN

    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
//    line l;
//    l.x1 = 40;
//    l.y1 = 20;
//    l.x2 = 40;
//    l.y2 = 40;
    int difx = 0;
    int dify = 2;
    int espera = 500;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
//        SDL_RenderDrawLine(ren, l.x1, l.y1, l.x2, l.y2);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        dify = -2;
                        difx = 0;
                        l.x1 += 10;
                        l.y1 -= 10;
                        l.x2 -= 10;
                        l.y2 += 10;
                        break;
                    case SDLK_DOWN:
                        dify = 2;
                        difx = 0;
                        l.x1 += 10;
                        l.y1 -= 10;
                        l.x2 -= 10;
                        l.y2 += 10;
                        break;
                    case SDLK_LEFT:
                        difx = -2;
                        dify = 0;
                        l.x1 -= 10;
                        l.y1 += 10;
                        l.x2 += 10;
                        l.y2 -= 10;
                        break;
                    case SDLK_RIGHT:
                        difx = 2;
                        dify = 0;
                        l.x1 -= 10;
                        l.y1 += 10;
                        l.x2 += 10;
                        l.y2 -= 10;
                        break;
                }
            }
        } else {
            espera = 500;
            l.x1 += difx;
            l.y1 += dify;
            l.x2 += difx;
            l.y2 += dify;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
