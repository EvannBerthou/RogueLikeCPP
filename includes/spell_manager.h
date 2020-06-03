#ifndef SPELL_MANAGER_H
#define SPELL_MANAGER_H

#include <vector>
#include "camera.h"
#include "textures.h"
#include "spell.h"
#include "vec2.h"
#include "room.h"

typedef struct {
    std::vector<spell_t> spells = {{}};
    void select_spell(camera_t &camera, vec2i player_position, vec2i mouse_position);
    void render(camera_t &camera, texture_dict &textures, vec2i mouse_position);
    void cast(camera_t &camera, vec2i mouse_position, room_t *room);
    int selected_spell = -1;
} spells_t;

#endif
