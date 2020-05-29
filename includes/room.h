#ifndef ROOM_H
#define ROOM_H

#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "tile.h"
#include "world_item.h"
#include "chest.h"
#include "camera.h"

typedef struct room_t {
    int x,y;
    std::array<room_t*, 4> doors = {NULL};
    std::vector<tile_t> tiles = {};
    std::vector<world_item_t> items = {};
    std::vector<chest_t> chests = {};
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

    void remove_item(world_item_t *to_remove) {
        for (std::vector<world_item_t>::size_type i = 0; i < items.size(); i++)
            if (&items.at(i) == to_remove) {
                items.erase(items.begin() + i);
                return;
            }
    }

    void render (camera_t &camera, int offset);
} room_t;

#endif
