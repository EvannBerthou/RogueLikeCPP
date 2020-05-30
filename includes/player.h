#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "room.h"
#include "camera.h"
#include "textures.h"
#include "spell_manager.h"
#include "inventory.h"
#include "vec2.h"
#include "slot.h"

typedef struct {
    room_t *in_room;
    int x = 7, y = 5;
    double frame_time = 0;
    int frame = 0;
    int frame_count = 4;
    bool facing_left = true;

    int max_health = 100;
    int health = max_health;
    inventory_t inventory = {};
    spells_t spells = {};

    void update(double dt);
    void move(SDL_Event event, camera_t *camera);
    void render(camera_t &camera, int offset, texture_dict &characters_textures);
    void consume(vec2i mouse_position);
    void consume(item_t *item);
} player_t;

#endif
