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

vec2i get_next_tile_pos(int dir, vec2i pos) {
    int x = pos.x;
    int y = pos.y;
    switch (dir){
    case 0:  return vec2i(x,y-1);
    case 1:  return vec2i(x+1,y);
    case 2:  return vec2i(x,y+1);
    case 3:  return vec2i(x-1,y);
    }
    return vec2i(x,y);
}

bool player_t::move(SDL_Event event, camera_t *camera) {
    if (inventory.active) return false;
    if (event.key.keysym.sym == SDLK_q) facing_left = true;
    if (event.key.keysym.sym == SDLK_d) facing_left = false;
    vec2i next_pos = get_next_tile_pos(get_direction_from_keycode(event.key.keysym.sym),pos);
    if (in_room->has_chest(next_pos)) {
        std::cout << "chest" << std::endl;
        return false;
    }

    world_item_t *item_on_ground = in_room->has_item(next_pos);
    bool return_value = false;
    if (item_on_ground != NULL) {
        inventory.add_item(&item_on_ground->item);
        in_room->remove_item(item_on_ground);
    }

    if (in_room->enemy_at(next_pos) != NULL) {
        return false;
    }

    if (next_pos != pos && !in_room->get_tile_at_xy(next_pos)->blocking) {
        pos = next_pos;
        return_value = true;
    }

    if (in_room->get_tile_at_xy(pos)->door){
        int dir = get_direction_from_keycode(event.key.keysym.sym);
        if (dir != -1){
            if (in_room->doors[dir] != NULL){
                room_t *new_room = in_room->doors[dir];
                camera->begin_transistion(in_room->pos, new_room->pos);
                prev_room = in_room;
                in_room = new_room;
                switch(dir){
                    case 0: pos = {7,9}; break;
                    case 1: pos = {1,5}; break;
                    case 2: pos = {7,1}; break;
                    case 3: pos = {13,5}; break;
                }
            }
        }
    }
    if (spells.selected_spell != -1)
        spells.spells.at(spells.selected_spell).set_spell_zone(pos);
    return return_value;
}

void player_t::render(camera_t &camera, int offset, texture_dict &characters_textures) {
    SDL_Rect player_rect;

    int center_x = camera.w / 2 - (15*camera.tile_size + camera.tile_size) / 2;
    int center_y = camera.h / 2 - (11*camera.tile_size + camera.tile_size) / 2;

    player_rect = {pos.x * camera.tile_size + center_x + in_room->pos.x * (15 * camera.tile_size + offset),
                   pos.y * camera.tile_size + center_y + in_room->pos.y * (11 * camera.tile_size + offset),
                   camera.tile_size, camera.tile_size};
    std::string texture_to_load = "player" + std::to_string(this->frame);
    camera.render_texture(characters_textures.get_texture_by_name(texture_to_load),
                          &player_rect, this->facing_left);

    SDL_Rect health_rect = {5,5, (int)(stats.health * 1.5), 30};
    camera.render_fill_rect_static({222,23,56,255}, &health_rect);

}

void player_t::consume(item_t *item) {
    if (!inventory.active) return;
    if (item == NULL) return;

    if (item->type == ItemType::Effect){
        if (item->effect == ItemEffect::Heal)
            regen_health(item->amount);
        if (item->effect == ItemEffect::Damage)
            take_damage(item->amount);
        inventory.remove_item(item);
    }
}


void player_t::take_damage(int amount) {
    stats.health -= amount;
    if (stats.health <= 0) {
        stats.alive = false;
        stats.health = 0;
        std::cout << "game over" << std::endl;
    }
}

void player_t::regen_health(int amount) {
    stats.health += amount;
    if (stats.health > stats.max_health) stats.health = stats.max_health;
}

bool player_t::physical_damage(camera_t &camera, vec2i mouse_position, room_t *room) {
    enemy_t *enemy = room->enemy_at(camera.vec2_screen_to_room(mouse_position));
    if (enemy != NULL) {
        if (distance(camera.vec2_screen_to_room(mouse_position), pos) < 2.0f) {
            enemy->take_damage(stats.strength);
            return true;
        }
    }
    return false;
}
