#ifndef STATS_H
#define STATS_H

#include <SDL2/SDL_ttf.h>
#include "camera.h"
#include "textures.h"
#include "fonts.h"

int constexpr stats_width  = 400;
int constexpr stats_height = 200;

typedef struct {
    int health;
    int max_health;
    int strength;

    bool alive = true;
    bool active = false;

    void render(camera_t &camera, texture_dict &texture, TTF_Font *font);
} stats_t;

#endif
