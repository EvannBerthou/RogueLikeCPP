#ifndef STATS_H
#define STATS_H

#include "camera.h"
#include "textures.h"
#include "fonts.h"
#include "vec2.h"

typedef struct {
    int health;
    int max_health;
    int base_strength;
    int base_magic;

    int strength = base_strength;
    int magic = base_magic;

    bool alive = true;

    void render(camera_t &camera, TTF_Font *font, vec2i offset);
} stats_t;

#endif
