#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "camera.h"
#include "stats.h"

typedef struct ennemy_t {
    int x,y;
    SDL_Texture *texture;
    stats_t stats = {100,100,100};
    bool alive = true;

    void take_damage(int amount);
} enemy_t;

#endif
