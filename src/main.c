#include "circle.h"
#include "constants.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void panic()
{
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: %s", SDL_GetError());
    SDL_Quit();
    exit(1);
}

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        panic();
    SDL_Window *win =
        SDL_CreateWindow("bouncy", WIN_W, WIN_H, SDL_WINDOW_BORDERLESS);
    if (!win)
        panic();

    // raise the window
    if (!SDL_RaiseWindow(win))
        panic();

    SDL_Surface *win_surface = SDL_GetWindowSurface(win);
    if (!win_surface)
        panic();

    struct Circle cir = (struct Circle){
        .x = 100,
        .y = 100,
        .r = 50,
        .col = 0xffeeeeee,
        .vx = 4,
    };

    uint8_t running = 1;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_EVENT_QUIT:
                running = 0;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (e.key.key == SDLK_ESCAPE)
                    running = 0;
                break;
            }
        }

        SDL_FillSurfaceRect(win_surface, NULL, 0xff101010);

        CircleFill(win_surface, cir);
        CircleUpdate(&cir);

        SDL_UpdateWindowSurface(win);
        SDL_Delay(16); // ~60fps
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
