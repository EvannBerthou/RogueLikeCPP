#include <utility>
#include "spell.h"

static vec2i get_pos(int dir, int r) {
    switch (dir){
        case 0: return vec2i(0,-r);
        case 1: return vec2i(r,0);
        case 2: return vec2i(0,r);
        case 3: return vec2i(-r,0);
    }
    return vec2i(0,0);
}

static bool is_hovered(SDL_Rect &rect, vec2i mp) {
    return (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h);
}

vec2i* spell_t::get_hovered(camera_t &camera, vec2i mp) {
    int offset_x = (camera.w - (15 * 50)) / 2;
    int offset_y = (camera.h - (11 * 50)) / 2;
    for (auto &tile: spell_zone) {
        SDL_Rect rect = {tile.x * 50 + offset_x, tile.y * 50 + offset_y, 50,50};
        if (is_hovered(rect, mp)) return &tile;
    }
    return NULL;
}

void spell_t::set_spell_zone(vec2i pp) {
    spell_zone.clear();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < radius; ++j) {
            auto offset = get_pos(i,j);
            vec2i pos = pp + offset;
            if (pos.x <= 0 || pos.x >= 14 || pos.y <= 0 || pos.y >= 10) continue;
            spell_zone.push_back(pos);
        }
    }

    if (diagonal) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                vec2i pos = pp + vec2i(i,j);
                if (pos.x <= 0 || pos.x >= 14 || pos.y <= 0 || pos.y >= 10) continue;
                spell_zone.push_back(pos);
            }
        }
    }
}

void spell_t::render_zone(camera_t &camera, texture_dict &textures) {
    if (camera.in_transisition) return;
    for (auto &tile_pos: spell_zone) {
        SDL_Rect rect = {tile_pos.x, tile_pos.y, camera.tile_size, camera.tile_size};
        camera.rect_room_to_screen(rect);
        camera.render_texture_to_room(textures.get_texture_by_name("hovered"), tile_pos);
    }
}
