#ifndef ROOM_H
#define ROOM_H

#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "tile.h"
#include "world_item.h"
#include "camera.h"
#include "chest.h"
#include "vec2.h"
#include "enemy.h"
#include "textures.h"

typedef struct room_t {
    vec2i pos;
    std::array<room_t*, 4> doors = {NULL};
    std::vector<tile_t> tiles = {};
    std::vector<world_item_t> items = {};
    std::vector<chest_t> chests = {};
    std::vector<enemy_t> enemies = {};
    SDL_Texture *static_texture = NULL;

    bool operator==(const room_t& other){
        return pos == other.pos;
    }

    tile_t *get_tile_at_xy(vec2i tile_pos){
        return &tiles.at(tile_pos.y * 15 + tile_pos.x);
    }

    void set_tile_at_xy(int x, int y, tile_t tile){
        tiles.at(y * 15 + x) = tile;
    }

    bool is_wall(vec2i tile_pos) {
        return tile_pos.x == 0 || tile_pos.y == 0 || tile_pos.x == 14 || tile_pos.y == 10;
    }

    chest_t *has_chest(vec2i tile_pos) {
        for (auto &chest : chests)
            if (chest.pos == tile_pos) return &chest;
        return NULL;
    }

    world_item_t *has_item(vec2i tile_pos) {
        for (auto &item : items)
            if (item.pos == tile_pos) return &item;
        return NULL;
    }

    enemy_t *enemy_at(vec2i tile_pos) {
        for (auto &enemy : enemies)
            if (enemy.pos == tile_pos) return &enemy;
        return NULL;
    }

    void remove_item(world_item_t *to_remove) {
        for (std::vector<world_item_t>::size_type i = 0; i < items.size(); i++)
            if (&items.at(i) == to_remove) {
                items.erase(items.begin() + i);
                return;
            }
    }

    void remove_chest(chest_t *chest) {
        for (std::vector<chest_t>::size_type i = 0; i < chests.size(); i++)
            if (&chests.at(i) == chest) {
                chests.erase(chests.begin() + i);
                return;
            }
    }

    void render (camera_t &camera, int offset, texture_dict &textures);
    void update (float dt);
} room_t;

#endif
