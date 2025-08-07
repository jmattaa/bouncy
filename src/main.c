#include "circle.h"
#include "constants.h"
#include <SDL3/SDL.h>
#include <math.h>
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
    srand(time(NULL));

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

    size_t ncircles = 1;
    struct Circle *circles = calloc(ncircles, sizeof(struct Circle));
    if (!circles)
        panic();
    circles[0] = (struct Circle){
        .x = (double)WIN_W / 2,
        .y = (double)WIN_H / 2,
        .r = 10,
        .vx = rand() % 100 - 50,
        .vy = 0,
        .col = 0xff << 24 | rand() % 0xffffff, // hihi
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
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    for (size_t i = 0; i < ncircles; i++)
                    {
                        struct Circle *cir = &circles[i];
                        const double dx = e.motion.x - cir->x;
                        const double dy = e.motion.y - cir->y;

                        cir->vx += dx * .08;
                        cir->vy += dy * .08;
                    }
                }
                if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    ncircles++;
                    circles =
                        realloc(circles, ncircles * sizeof(struct Circle));
                    if (!circles)
                        panic();

                    circles[ncircles - 1] = (struct Circle){
                        .x = e.motion.x,
                        .y = e.motion.y,
                        .r = 10,
                        .vx = rand() % 100 - 50,
                        .vy = 0,
                        .col = 0xff << 24 | rand() % 0xffffff, // hihi
                    };
                }
                break;
            }
        }

        SDL_FillSurfaceRect(win_surface, NULL, 0xff101010);

        for (size_t i = 0; i < ncircles; i++)
        {
            struct Circle *cir = &circles[i];
            CircleFill(win_surface, *cir);
            CircleUpdate(cir);
        }

        SDL_UpdateWindowSurface(win);
        SDL_Delay(16); // ~60fps
    }

    free(circles);

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
