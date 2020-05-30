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

static bool is_hovered(SDL_Rect &rect, vec2i mp) {
    return (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h);
}

std::pair<int,int> * spell_t::get_hovered(vec2i mp) {
    for (auto &tile: spell_zone) {
        SDL_Rect rect = {tile.first * 50 + 25, tile.second * 50 + 25, 50,50};
        if (is_hovered(rect, mp)) return &tile;
    }
    return NULL;
}

void spell_t::set_spell_zone(vec2i pp) {
    spell_zone.clear();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < radius; ++j) {
            auto offset = get_pos(i,j);
            vec2i pos = { pp.x + offset.first, pp.y + offset.second };
            if (pos.x == 0 || pos.x == 14 || pos.y == 0 || pos.y == 10) continue;
            spell_zone.push_back(std::make_pair(pos.x, pos.y));
        }
    }
}

void spell_t::render_zone(camera_t &camera, texture_dict &textures, vec2i mp) {
    if (camera.in_transisition) return;
    for (auto &tile: spell_zone) {
        SDL_Rect rect = {tile.first, tile.second, camera.tile_size, camera.tile_size};
        camera.rect_room_to_screen(rect);
        if (is_hovered(rect, mp))
            camera.render_texture_to_room(textures.get_texture_by_name("selected"),
                                          {tile.first, tile.second});
        else
            camera.render_texture_to_room(textures.get_texture_by_name("hovered"),
                                          {tile.first, tile.second});
    }
}
