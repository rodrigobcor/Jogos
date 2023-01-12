#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40, 20, 10,10 };
    SDL_Rect s = { 100, 20, 10,10 };
    SDL_Rect t = { 160, 20, 10,10 };
    SDL_Event evt;
    int wait;

    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderFillRect(ren, &s);
        SDL_RenderFillRect(ren, &t);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, wait);
        if (isevt) {
            wait -= (SDL_GetTicks() - antes);
            if (wait < 0) {
                wait = 0;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        s.y -= 5;
                        break;
                    case SDLK_DOWN:
                        s.y += 5;
                        break;
                    case SDLK_LEFT:
                        s.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        s.x += 5;
                        break;
                }
            } else if (evt.type == SDL_MOUSEMOTION){
                t.x = evt.motion.x;
                t.y = evt.motion.y;
            }
        } else {
            wait = 500;
            r.x += 2;
            r.y += 2;
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
