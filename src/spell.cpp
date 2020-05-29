#include <utility>
#include "spell.h"

static std::pair<int,int> get_pos(int dir, int r) {
    switch (dir){
        case 0: return std::make_pair(0,-r);
        case 1: return std::make_pair(r,0);
        case 2: return std::make_pair(0,r);
        case 3: return std::make_pair(-r,0);
    }
    return std::make_pair(0,0);
}

static bool is_hovered(SDL_Rect &rect, int m_x, int m_y) {
    return (m_x > rect.x && m_x < rect.x + rect.w && m_y > rect.y && m_y < rect.y + rect.h);
}

std::pair<int,int> * spell_t::get_hovered(camera_t &camera, int m_x, int m_y) {
    for (auto &tile: spell_zone) {
        SDL_Rect rect = {tile.first * 50 - (int)camera.x, tile.second * 50 - (int)camera.y, 50,50};
        if (is_hovered(rect, m_x, m_y)) return &tile;
    }
    return NULL;
}

void spell_t::set_spell_zone(int c_x, int c_y) {
    spell_zone.clear();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < radius; ++j) {
            auto offset = get_pos(i,j);
            vec2i pos = { c_x + offset.first, c_y + offset.second };
            if (pos.x == 0 || pos.x == 14 || pos.y == 0 || pos.y == 10) continue;
            spell_zone.push_back(std::make_pair(pos.x, pos.y));
        }
    }
}

void spell_t::render_zone(camera_t &camera, texture_dict &textures, int m_x, int m_y) {
    if (camera.in_transisition) return;
    for (auto &tile: spell_zone) {
        SDL_Rect rect = {tile.first * 50 + 25, tile.second * 50 + 25, 50,50};
        if (is_hovered(rect, m_x, m_y))
            camera.render_texture_static(textures.get_texture_by_name("selected"), &rect);
        else
            camera.render_texture_static(textures.get_texture_by_name("hovered"),  &rect);
    }
}
