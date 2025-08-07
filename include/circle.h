#ifndef _BOUNCY_CIRCLE_H
#define _BOUNCY_CIRCLE_H

#include <SDL3/SDL.h>
#include <stdint.h>

struct Circle
{
    double x, y, r, vx, vy;
    uint32_t col;
};

void CircleFill(SDL_Surface *sur, struct Circle cir);
void CircleUpdate(struct Circle *cir);

#endif
