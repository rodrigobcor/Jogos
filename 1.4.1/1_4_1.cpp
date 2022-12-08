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
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    bool quit = false;

    SDL_Rect rect[10];
    int cont = 0;

    while (!quit) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        for (int i = 0; i<10;i++){
            SDL_RenderFillRect(ren, &rect[i]);
        }
        SDL_RenderPresent(ren);

        while (SDL_PollEvent(&evt) != 0){
            if (evt.type == SDL_QUIT){
                quit = true;
            } else if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (r.y>0){
                            r.y -= 5;
                        } else {
                            r.y += 5;
                        }
                        break;
                    case SDLK_DOWN:
                        if (r.y<95){
                            r.y += 5;
                        } else {
                            r.y -= 5;
                        }
                        break;
                    case SDLK_LEFT:
                        if (r.x>0){
                            r.x -= 5;
                        } else {
                            r.x += 5;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (r.x<195){
                            r.x += 5;
                        } else {
                            r.x -= 5;
                        }
                        break;
                }
            } else if (evt.type == SDL_MOUSEBUTTONDOWN){
                rect[cont].x = evt.button.x;
                rect[cont].y = evt.button.y;
                rect[cont].w = 10;
                rect[cont].h = 10;
                cont++;
            }
        }
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();

}
