#ifndef SPELL_H
#define SPELL_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "textures.h"
#include "camera.h"
#include "vec2.h"

typedef struct {
    int radius;
    int damage;
    bool diagonal;
    int cooldown = 3;
    int remaining_cooldown = 0;

    SDL_Texture *texture = NULL;

    std::vector<vec2i> spell_zone = {};

    void set_spell_zone(vec2i pp);
    vec2i* get_hovered(camera_t &camera, vec2i mp);
    void render_zone(camera_t &camera, texture_dict &textures);
} spell_t;

#endif
