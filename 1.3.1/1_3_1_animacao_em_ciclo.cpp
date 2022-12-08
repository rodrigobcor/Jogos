#include <SDL2/SDL.h>

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
    SDL_Point p = { 40,20 };
    int i = 0;
    int contx= 0;
    int conty = 0;
    while (i<500) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        for( int size = 0; size < 10 + contx + conty; size += 1 ){
            if (contx%2==0 && conty%2==0){
                SDL_RenderDrawPoint( ren, p.x - size, p.y - size );
            } else if (contx%2==0 && conty%2!=0){
                SDL_RenderDrawPoint( ren, p.x - size, p.y + size );
            } else if (contx%2!=0 && conty%2==0){
                SDL_RenderDrawPoint( ren, p.x + size, p.y - size );
            } else if (contx%2!=0 && conty%2!=0){
                SDL_RenderDrawPoint( ren, p.x + size, p.y + size );
            }
        }
        SDL_RenderPresent(ren);
        SDL_Delay(500);
        if (contx%2==0){
            p.x += 4;
        } else {
            p.x -= 4;
        }
        if (p.x >= 200 || p.x <= 0){
            contx++;
        }
        if (conty%2==0){
            p.y += 4;
        } else {
            p.y -= 4;
        }
        if (p.y >= 100 || p.y <= 0){
            conty++;
        }
        i++;
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
