#ifndef SPELL_H
#define SPELL_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "textures.h"
#include "camera.h"
#include "vec2.h"

typedef struct {
    int radius = 2;
    SDL_Texture *texture = NULL;
    std::vector<std::pair<int,int>> spell_zone = {};
    void set_spell_zone(vec2i pp);
    std::pair<int,int>* get_hovered(vec2i mp);
    void render_zone(camera_t &camera, texture_dict &textures, vec2i mp);
} spell_t;

#endif
