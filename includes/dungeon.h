#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <SDL2/SDL.h>
#include "textures.h"
#include "room.h"

typedef std::unordered_map<std::string, item_t> items_map;

typedef struct {
    std::vector<room_t> rooms;

    void free() {
        for (auto const &room: rooms)
            SDL_DestroyTexture(room.static_texture);
    }

} dungeon_t;

dungeon_t generate_dungeon(int seed, int number_of_rooms);
SDL_Texture *get_texture_from_position(texture_dict &textures, int x, int y);
SDL_Texture *get_door_texture(texture_dict &textures, int side);
void generate_tiles(dungeon_t *d, texture_dict &textures, SDL_Renderer *renderer);
void generate_enemies(dungeon_t *d, texture_dict &textures, items_map &items);

#endif
