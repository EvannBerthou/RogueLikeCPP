#include <iostream>
#include "player.h"

player_t create_player(room_t *current_room, texture_dict &textures) {
    player_t player = {};
    player.in_room = current_room;
    player.prev_room = NULL;
    player.pos = vec2i(7,5);
    player.anim = load_animation(textures, "player");
    player.facing_left = true;
    player.moving_delay = 0;

    player.stats = {100,100,25,0};
    player.inventory = {};
    player.spells = {};

    player.in_chest = NULL;

    player.render_equipment_menu = false;
    player.base_offset = vec2i(0,0);
    player.spacing = vec2i(0,0);

    player.inventory.init_inventory();
    player.init_equipment();

    player.spells.spells.at(0).texture = textures.get_texture_by_name("wand");
    player.spells.spells.at(1).texture = textures.get_texture_by_name("wand");
    player.spells.spells.at(2).texture = textures.get_texture_by_name("wand");
    player.spells.spells.at(3).texture = textures.get_texture_by_name("wand");

    return player;
}

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
    anim.update(dt);
    if (moving_delay > 0) {
        moving_delay -= dt;
        std::cout << moving_delay << std::endl;
    }
}

vec2i get_next_tile_pos(int dir, vec2i pos) {
    switch (dir){
    case 0:  return pos + vec2i(0, -1);
    case 1:  return pos + vec2i(1,  0);
    case 2:  return pos + vec2i(0,  1);
    case 3:  return pos + vec2i(-1, 0);
    }
    return pos;
}

bool player_t::move(SDL_Event event, camera_t *camera) {
    if (inventory.active) return false;
    if (moving_delay > 0) return false;
    if (event.key.keysym.sym == SDLK_q) facing_left = true;
    if (event.key.keysym.sym == SDLK_d) facing_left = false;

    vec2i next_pos = get_next_tile_pos(get_direction_from_keycode(event.key.keysym.sym), pos);

    if (in_room->has_chest(next_pos))
        return false;

    world_item_t *item_on_ground = in_room->has_item(next_pos);
    bool return_value = false;
    if (item_on_ground != NULL) {
        inventory.add_item(item_on_ground->item);
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
                    case 0: pos = vec2i(7,9); break;
                    case 1: pos = vec2i(1,5); break;
                    case 2: pos = vec2i(7,1); break;
                    case 3: pos = vec2i(13,5); break;
                }
            }
        }
    }
    if (spells.selected_spell != -1)
        spells.spells.at(spells.selected_spell).set_spell_zone(pos);
    moving_delay = 150; // ms
    return return_value;
}

void player_t::render(camera_t &camera, int offset) {

    int center_x = camera.w / 2 - (15*camera.tile_size + camera.tile_size) / 2;
    int center_y = camera.h / 2 - (11*camera.tile_size + camera.tile_size) / 2;

    SDL_Rect player_rect;
    player_rect = {pos.x * camera.tile_size + center_x + in_room->pos.x * (15 * camera.tile_size + offset),
                   pos.y * camera.tile_size + center_y + in_room->pos.y * (11 * camera.tile_size + offset),
                   camera.tile_size, camera.tile_size};
    anim.render(camera, &player_rect, facing_left);

    SDL_Rect health_rect = {5,5, (int)(stats.health * 1.5), 30};
    camera.render_fill_rect_static({222,23,56,255}, &health_rect);
}

void player_t::init_equipment() {
    for (size_t i = 0; i < EQUIPMENT_SLOTS; i++)
        equipped_items[i].id = -1;
}

void player_t::render_equipment(camera_t &camera, texture_dict &textures, TTF_Font *font) {
    if(!render_equipment_menu)
        return;

    vec2i size = vec2i((SLOT_SIZE * 2 + 275), (SLOT_SIZE * 3 + 75)) * camera.scale;
    base_offset = vec2i(camera.w / 2 - size.x / 2, camera.h / 2 - size.y / 2);
    spacing = vec2i(30, 40) * camera.scale;

    SDL_Rect bg_rect = { base_offset.x, base_offset.y, size.x, size.y };
    camera.render_texture_static(textures.get_texture_by_name("ui_bg"), &bg_rect);

    stats.render(camera, font, {base_offset.x + 2 * inventory.slot_size + spacing.x,
                                base_offset.y + spacing.y});

    for (int i = 0; i < EQUIPMENT_SLOTS; i++)
    {
        SDL_Rect slot_rect = { i % 2 * inventory.slot_size + base_offset.x + spacing.x,
                               i / 2 * inventory.slot_size + base_offset.y + spacing.y,
                               inventory.slot_size, inventory.slot_size};
        camera.render_texture_static(textures.get_texture_by_name("slot"), &slot_rect);

        if (equipped_items[i].id > 0) {
            scale_rect(slot_rect, 0.75);
            if (equipped_items[i].texture == NULL)
                std::cout << "no texture for this slot " << i  << std::endl;
            camera.render_texture_static(equipped_items[i].texture, &slot_rect);
        }
    }
}

item_t *player_t::hovered_equipment(vec2i mp) {
    if (!render_equipment_menu)
        return NULL;

    for (int i = 0; i < EQUIPMENT_SLOTS; i++)
    {
        SDL_Rect rect = { i % 2 * inventory.slot_size + base_offset.x + spacing.x,
                          i / 2 * inventory.slot_size + base_offset.y + spacing.x,
                          inventory.slot_size, inventory.slot_size};
        if (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h) {
            item_t *item = &equipped_items[i];
            if (item->id > 0)
                return item;
        }
    }
    return NULL;
}

void player_t::consume(item_t *item) {
    if (!inventory.active) return;
    if (item == NULL) return;

    if (item->type == ItemType::Undefined)
        return;

    if (item->type == ItemType::Effect){
        if (item->effect == ItemEffect::Heal)
            regen_health(item->amount);
        if (item->effect == ItemEffect::Damage)
            take_damage(item->amount);
        inventory.remove_item(item);
    }
    else {
        item_t old_item = equipped_items[item->type];
        equipped_items[item->type] = *item;
        inventory.remove_item(item);

        if (old_item.id > 0)
            inventory.add_item(old_item);

        if (item->type == ItemType::Sword)
            stats.strength = stats.base_strength + equipped_items[item->type].amount;

        if (item->type == ItemType::Wand)
            stats.magic = stats.base_magic + equipped_items[item->type].amount;
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

bool player_t::cast(camera_t &camera, vec2i mp, room_t *room) {
    return spells.cast(camera, mp, room, stats.magic);
}
