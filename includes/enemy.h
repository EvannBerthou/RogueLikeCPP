#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <vector>
#include "camera.h"
#include "stats.h"
#include "vec2.h"
#include "item.h"

typedef struct enemy_t {
    vec2i pos;
    SDL_Texture *texture;
    stats_t stats = {100,100,10,0};
    bool battle_started = false;
    std::vector<item_t*> drop_table = {};

    bool take_damage(int amount);
    void render(camera_t &camera, vec2i offset);
} enemy_t;

#endif
