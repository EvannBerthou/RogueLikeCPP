#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "dungeon.h"
#include "room.h"

bool get_new_room(std::vector<room_t> &rooms){
    room_t *random_room = &rooms.at(rand() % rooms.size());
    int side = rand()%4;
    if (random_room->doors[side] != NULL) return false;

    auto new_room_pos = get_new_pos(random_room->x, random_room->y, side);
    room_t new_room = {new_room_pos.first, new_room_pos.second};
    if (room_exists(rooms, new_room)) return false;
    rooms.push_back(new_room);

    room_t *last_room = &rooms.back();
    random_room->doors[side] = last_room;
    last_room->doors[get_opposite_side(side)] = random_room;
    return true;
}

std::pair<int,int> get_door_pos(int side){
    switch (side){
    case 0: return std::make_pair(7,0);
    case 1: return std::make_pair(14,5);
    case 2: return std::make_pair(7,10);
    case 3: return std::make_pair(0,5);
    }
    return std::make_pair(-1,-1);
}

int get_opposite_side(int side){
    if (side == 0) return 2;
    if (side == 1) return 3;
    if (side == 2) return 0;
    if (side == 3) return 1;
    return -1;
}

std::pair<int,int> get_new_pos(int x, int y, int dir){
    switch (dir){
    case 0: return std::make_pair(x,y-1);
    case 1: return std::make_pair(x+1,y);
    case 2: return std::make_pair(x,y+1);
    case 3: return std::make_pair(x-1,y);
    }
    return std::make_pair(-1,-1);
}

bool room_exists(std::vector<room_t> &rooms, room_t &room){
    return std::find(rooms.begin(), rooms.end(), room) != rooms.end();
}


dungeon_t generate_dungeon(int seed, int n_w, int n_h, int number_of_rooms) {
    srand(seed);
    dungeon_t d;
    d.rooms.reserve(number_of_rooms);

    if (number_of_rooms > n_w * n_h) {
        printf("Plus de rooms que de place disponible (%d >= %d)\n", number_of_rooms, (n_w*n_h));
        exit(1);
    }

    d.rooms.push_back({0,0});
    room_t first_room = d.rooms.at(0);

    int dir = rand()%4;
    auto second_room_pos = get_new_pos(first_room.x, first_room.y, dir);
    d.rooms.push_back({second_room_pos.first, second_room_pos.second});

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
                SDL_Rect position = {door_pos.first * 50, door_pos.second * 50, 50,50};
                SDL_RenderCopy(renderer, text, NULL, &position);
                room.set_tile_at_xy(door_pos.first, door_pos.second, {false,true});
            }
        }
        room.static_texture = static_texture;
        SDL_SetRenderTarget(renderer, NULL);
    }
}
