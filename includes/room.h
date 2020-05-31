#ifndef ROOM_H
#define ROOM_H

#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "tile.h"
#include "world_item.h"
#include "enemy.h"
#include "camera.h"
#include "chest.h"

typedef struct room_t {
    int x,y;
    std::array<room_t*, 4> doors = {NULL};
    std::vector<tile_t> tiles = {};
    std::vector<world_item_t> items = {};
    std::vector<chest_t> chests = {};
    std::vector<enemy_t> enemies = {};
    SDL_Texture *static_texture = NULL;

    bool operator==(const room_t other){
        return other.x == x && other.y == y;
    }

    tile_t *get_tile_at_xy(int x, int y){
        return &tiles.at(y * 15 + x);
    }

    void set_tile_at_xy(int x, int y, tile_t tile){
        tiles.at(y * 15 + x) = tile;
    }

    chest_t *has_chest(int x, int y) {
        for (auto &chest : chests)
            if (chest.x == x && chest.y == y) return &chest;
        return NULL;
    }

    world_item_t *has_item(int x, int y) {
        for (auto &item : items)
            if (item.x == x && item.y == y) return &item;
        return NULL;
    }

    enemy_t *enemy_at(int x, int y) {
        for (auto &enemy : enemies)
            if (enemy.x == x && enemy.y == y) return &enemy;
        return NULL;
    }

    void remove_item(world_item_t *to_remove) {
        for (std::vector<world_item_t>::size_type i = 0; i < items.size(); i++)
            if (&items.at(i) == to_remove) {
                items.erase(items.begin() + i);
                return;
            }
    }

    void render (camera_t &camera, int offset);
    void update (float dt);
} room_t;

#endif
