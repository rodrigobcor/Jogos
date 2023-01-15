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
    SDL_Rect r = { 100, 20, 30,30 };
    SDL_Event evt;
    bool quit = false;
    SDL_Point clickOffset;
    SDL_Rect * selectedRect = NULL;
    bool leftMouseButtonDown = false;
    bool escape = false;
    int xOriginal, yOriginal;

    SDL_Point mousePos;

    while (!quit) {
        SDL_PollEvent(&evt);
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        switch (evt.type) {
            case SDL_KEYDOWN:
                if (SDLK_ESCAPE){
                    escape = true;
                    leftMouseButtonDown = false;
                    selectedRect = NULL;
                    r.x = xOriginal;
                    r.y = yOriginal;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (leftMouseButtonDown && evt.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = false;
                    selectedRect = NULL;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!leftMouseButtonDown && evt.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = true;
                    xOriginal = r.x;
                    yOriginal = r.y;
                    if (SDL_PointInRect(&mousePos, &r))
                    {
                        selectedRect = &r;
                        clickOffset.x = mousePos.x - r.x;
                        clickOffset.y = mousePos.y - r.y;
                        break;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                mousePos = { evt.motion.x, evt.motion.y };
//                if (escape){
//                    leftMouseButtonDown = false;
//                    selectedRect->x = xOriginal;
//                    selectedRect->y = yOriginal;
//                    escape = false;
//                }
                if (leftMouseButtonDown && selectedRect != NULL)
                {
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
