#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "room.h"
#include "camera.h"
#include "textures.h"
#include "spell_manager.h"
#include "inventory.h"
#include "vec2.h"
#include "stats.h"
#include "chest.h"
#include "animation.h"

int constexpr EQUIPMENT_SLOTS = 6;

typedef struct player_t {
    room_t *in_room;
    room_t *prev_room = NULL;
    vec2i pos = vec2i(7,5);
    animation_t anim = {};
    bool facing_left = true;

    stats_t stats = {100,100,25,0};
    inventory_t inventory = {};
    spells_t spells = {};

    chest_t *in_chest = NULL;

    item_t equipped_items[EQUIPMENT_SLOTS] = {};
    bool render_equipment_menu = false;
    vec2i base_offset = vec2i(0,0);
    vec2i spacing = vec2i(0,0);

    void init_equipment();
    void update(double dt);
    bool move(SDL_Event event, camera_t *camera);
    void render(camera_t &camera, int offset);
    void render_equipment(camera_t &camera, texture_dict &textures, TTF_Font *font);
    item_t *hovered_equipment(vec2i mp);
    void consume(item_t *item);
    bool physical_damage(camera_t &camera, vec2i mouse_position, room_t *room);
    bool cast(camera_t &camera, vec2i mp, room_t *room);

    void take_damage  (int amount);
    void regen_health (int amount);
} player_t;

#endif
