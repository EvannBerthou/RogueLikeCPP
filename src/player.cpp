#include <iostream>
#include "player.h"

int get_direction_from_keycode(int keycode){
    switch (keycode){
    case SDLK_z: return 0;
    case SDLK_d: return 1;
    case SDLK_s: return 2;
    case SDLK_q: return 3;
    }
    return -1;
}

void player_t::update(double dt) {
    frame_time += dt / 500;
    frame = ((int)frame_time) % frame_count;
}

std::pair<int,int> get_next_tile_pos(int dir, int x, int y) {
    switch (dir){
    case 0:  return std::make_pair(x,y-1);
    case 1:  return std::make_pair(x+1,y);
    case 2:  return std::make_pair(x,y+1);
    case 3:  return std::make_pair(x-1,y);
    }
    return std::make_pair(-1, -1);
}

void player_t::move(SDL_Event event, camera_t *camera) {
    if (inventory.active) return;
    if (event.key.keysym.sym == SDLK_q) facing_left = true;
    if (event.key.keysym.sym == SDLK_d) facing_left = false;
    std::pair<int, int> next_pos = get_next_tile_pos(get_direction_from_keycode(event.key.keysym.sym),x,y);
    if (in_room->has_chest(next_pos.first, next_pos.second)) {
        std::cout << "chest" << std::endl;
        return;
    }

    world_item_t *item_on_ground = in_room->has_item(next_pos.first, next_pos.second);
    if (item_on_ground != NULL) {
        inventory.add_item(&item_on_ground->item);
        in_room->remove_item(item_on_ground);
    }

    switch (event.key.keysym.sym){
    case SDLK_z:
        if (!in_room->get_tile_at_xy(x, y-1)->blocking)
            y -= 1;
        break;
    case SDLK_d:
        if (!in_room->get_tile_at_xy(x+1, y)->blocking)
            x += 1;
        break;
    case SDLK_s:
        if (!in_room->get_tile_at_xy(x, y+1)->blocking)
            y += 1;
        break;
    case SDLK_q:
        if (!in_room->get_tile_at_xy(x-1, y)->blocking)
            x -= 1;
        break;
    }
    if (in_room->get_tile_at_xy(x,y)->door){
        int dir = get_direction_from_keycode(event.key.keysym.sym);
        if (dir != -1){
            if (in_room->doors[dir] != NULL){
                room_t *new_room = in_room->doors[dir];
                camera->begin_transistion(in_room->x, in_room->y, new_room->x, new_room->y);
                in_room = new_room;
                switch(dir){
                    case 0:
                        x = 7;
                        y = 9;
                        break;
                    case 1:
                        x = 1;
                        y = 5;
                        break;
                    case 2:
                        x = 7;
                        y = 1;
                        break;
                    case 3:
                        x = 13;
                        y = 5;
                        break;
                }
            }
        }
    }
    if (spells.selected_spell != -1)
        spells.spells.at(spells.selected_spell).set_spell_zone(x, y);
}

void player_t::render(camera_t &camera, int offset, texture_dict &characters_textures) {
    SDL_Rect player_rect;
    player_rect = {this->x * camera.tile_size
                   + this->in_room->x * (15 * camera.tile_size + offset),
                   this->y * camera.tile_size
                   + this->in_room->y * (11 * camera.tile_size + offset),
                   camera.tile_size, camera.tile_size};
    std::string texture_to_load = "player" + std::to_string(this->frame);
    camera.render_texture(characters_textures.get_texture_by_name(texture_to_load),
                          &player_rect, this->facing_left);

    SDL_Rect health_rect = {5,5, (int)(this->health * 1.5), 30};
    camera.render_fill_rect_static({222,23,56,255}, &health_rect);

}
