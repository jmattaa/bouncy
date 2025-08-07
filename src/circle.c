#include "circle.h"
#include "constants.h"

void CircleFill(SDL_Surface *sur, struct Circle cir)
{
    const double low_x = cir.x - cir.r;
    const double low_y = cir.y - cir.r;
    const double high_x = cir.x + cir.r;
    const double high_y = cir.y + cir.r;

    const double r_squared = cir.r * cir.r;

    for (double x = low_x; x < high_x; x++)
    {
        for (double y = low_y; y < high_y; y++)
        {
            const double dx = x - cir.x;
            const double dy = y - cir.y;
            const double dist_squared = dx * dx + dy * dy;
            if (dist_squared <= r_squared)
                SDL_FillSurfaceRect(sur, &(SDL_Rect){x, y, 1, 1}, cir.col);
        }
    }
}

void CircleUpdate(struct Circle *cir)
{
    cir->x += cir->vx;
    cir->y += cir->vy;

    cir->vy += GRAVIY_ACC;

    if (cir->y + cir->r > WIN_H || cir->y - cir->r < 0)
    {
        cir->y = (cir->y + cir->r > WIN_H) ? WIN_H - cir->r : cir->r;
        cir->vy *= -BALL_BOUNCE_DAMP;
    }
    if (cir->x + cir->r > WIN_W || cir->x - cir->r < 0)
    {
        cir->x = (cir->x + cir->r > WIN_W) ? WIN_W - cir->r : cir->r;
        cir->vx *= -BALL_BOUNCE_DAMP;
    }
}
