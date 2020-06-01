#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "camera.h"
#include "stats.h"
#include "vec2.h"

typedef struct ennemy_t {
    vec2i pos;
    SDL_Texture *texture;
    stats_t stats = {100,100,100};
    bool alive = true;

    void take_damage(int amount);
} enemy_t;

#endif
