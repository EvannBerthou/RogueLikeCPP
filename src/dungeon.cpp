#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "dungeon.h"
#include "room.h"

static vec2i get_new_pos(vec2i pos, int dir){
    switch  (dir){
    case  0: return  vec2i(pos.x,   pos.y-1);
    case  1: return  vec2i(pos.x+1, pos.y);
    case  2: return  vec2i(pos.x,   pos.y+1);
    case  3: return  vec2i(pos.x-1, pos.y);
    }
    return vec2i(0,0);
}

static vec2i get_door_pos(int side){
    switch (side){
    case 0: return vec2i(7,0);
    case 1: return vec2i(14,5);
    case 2: return vec2i(7,10);
    case 3: return vec2i(0,5);
    }
    return vec2i(0,0);
}

static int get_opposite_side(int side){
    if (side == 0) return 2;
    if (side == 1) return 3;
    if (side == 2) return 0;
    if (side == 3) return 1;
    return -1;
}

static bool room_exists(std::vector<room_t> &rooms, room_t &room) {
    return std::find(rooms.begin(), rooms.end(), room) != rooms.end();
}

static bool get_new_room(std::vector<room_t> &rooms) {
    room_t *random_room = &rooms.at(rand() % rooms.size());
    int side = rand()%4;
    if (random_room->doors[side] != NULL) return false;

    auto new_room_pos = get_new_pos(random_room->pos, side);
    room_t new_room = {new_room_pos};
    if (room_exists(rooms, new_room)) return false;
    rooms.push_back(new_room);

    room_t *last_room = &rooms.back();
    random_room->doors[side] = last_room;
    last_room->doors[get_opposite_side(side)] = random_room;
    return true;
}

dungeon_t generate_dungeon(int seed, int number_of_rooms) {
    srand(seed);
    dungeon_t d;
    d.rooms.reserve(number_of_rooms);

    d.rooms.push_back({{0,0}});
    room_t first_room = d.rooms.at(0);

    int dir = rand()%4;
    auto second_room_pos = get_new_pos(first_room.pos, dir);
    d.rooms.push_back({second_room_pos});

    d.rooms.at(0).doors[dir] = &d.rooms.at(1);
    d.rooms.at(1).doors[get_opposite_side(dir)] = &d.rooms.at(0);

    int room_count = 2;
    while (room_count < number_of_rooms){
        if (get_new_room(d.rooms)) room_count++;
    }
    return d;
}

SDL_Texture *get_texture_from_position(texture_dict &textures, int x, int y) {
    if (y == 0 && x != 10)
        return textures.get_texture_by_name("wall_left");
    if (y == 14 && x != 10)
        return textures.get_texture_by_name("wall_right");
    if (x == 10 && y == 0)
        return textures.get_texture_by_name("wall_bottom_left");
    if (x == 10 && y == 14)
        return textures.get_texture_by_name("wall_bottom_right");
    if (x == 10 && y != 0 && y != 14)
        return textures.get_texture_by_name("wall_bottom");
    if (x == 0)
        return textures.get_texture_by_name("wall_top");
    return textures.get_texture_by_name("ground");
}

SDL_Texture *get_door_texture(texture_dict &textures, int side){
    switch (side){
    case 0:
        return textures.get_texture_by_name("door_front");
    case 1:
        return textures.get_texture_by_name("door_side_right");
    case 2:
        return textures.get_texture_by_name("door_back");
    case 3:
        return textures.get_texture_by_name("door_side_left");
    }
    return NULL;
}

void generate_tiles(dungeon_t *d, texture_dict &textures, SDL_Renderer *renderer) {
    for (auto &room: d->rooms){
        SDL_Texture *static_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET, 15*50,11*50);
        SDL_SetRenderTarget(renderer, static_texture);
        room.tiles.reserve(11*15);
        room.tiles.resize(11*15);
        for (int i = 0; i < 11; ++i){
            for (int j = 0; j < 15; j++){
                SDL_Texture *text = get_texture_from_position(textures, i,j);
                bool collide = text != textures.get_texture_by_name("ground");
                SDL_Rect position = {j * 50, i * 50, 50,50};
                SDL_RenderCopy(renderer, text, NULL, &position);
                room.tiles[i*15+j] = {collide, false};
            }
        }
        for (size_t i = 0; i < 4; ++i){
            if (room.doors.at(i) != NULL){
                auto door_pos = get_door_pos(i);
                SDL_Texture *text = get_door_texture(textures, i);
                SDL_Rect position = {door_pos.x * 50, door_pos.y * 50, 50,50};
                SDL_RenderCopy(renderer, text, NULL, &position);
                room.set_tile_at_xy(door_pos.x, door_pos.y, {false,true});
            }
        }
        room.static_texture = static_texture;
        SDL_SetRenderTarget(renderer, NULL);
    }
}

void generate_enemies(dungeon_t *d, texture_dict &textures, items_map &items) {
    for (auto &room: d->rooms) {
        int enemies_count = rand() % 5;
        for (int i = 0; i < enemies_count; ++i) {
            vec2i position = {rand() % 13 + 1, rand() % 8 + 1};
            room.enemies.push_back({position, textures.get_texture_by_name("ennemy")});
            room.enemies.at(i).drop_table.push_back(&items["wand"]);
        }
    }
}
