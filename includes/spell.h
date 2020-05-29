#ifndef SPELL_H
#define SPELL_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "textures.h"
#include "camera.h"

typedef struct {
    int radius = 2;
    SDL_Texture *texture = NULL;
    std::vector<std::pair<int,int>> spell_zone = {};
    void set_spell_zone(int c_x, int c_y);
    std::pair<int,int>* get_hovered(camera_t &camera, int m_x, int m_y);
    void render_zone(camera_t &camera, texture_dict &textures, int m_x, int m_y);
} spell_t;

#endif
